const { apiDomain } = require("../../../config");

const request = (options) => {
  console.log('[网络请求] 开始请求', options.url, '请求参数:', options.data || '无参数');
  return new Promise((resolve, reject) => {
    wx.request({
      ...options,
      success: (res) => {
        console.log('[网络请求] 请求成功', options.url, '状态码:', res.statusCode, '返回数据:', res.data);
        if (res.statusCode >= 200 && res.statusCode < 300) {
          resolve(res.data)
        } else {
          console.error('[网络请求] 请求失败', options.url, '错误状态码:', res.statusCode);
          reject(new Error(`HTTP ${res.statusCode}: ${res.data?.msg || '请求失败'}`))
        }
      },
      fail: (err) => {
        console.error('[网络请求] 请求异常', options.url, '错误信息:', err);
        reject(new Error(`网络错误: ${err.errMsg}`))
      }
    })
  })
}

Page({
  data: {
    isRefreshing: false,
    // 基础数据
    challengeId: '',
    teamId: '',
    
    // 挑战信息
    challengeData: {
      title: '加载中...',
      description: '',
      image: '/assets/default-challenge.png',
      totalParticipants: 0,
      startTime: '',
      endTime: '',
      location: null,
      needFaceVerify: false
    },
    
    // 数据状态
    _rawParticipants: [],    // 原始数据（保持引用）
    filteredParticipants: [], // 显示数据
    filterIndex: 0,
    statusFilterMap: ['all', '0', '1', '2'], // 修正顺序：全部、待审核、已通过、已拒绝
    
    // 统计数字（基于全部数据）
    stats: {
      total: 0,
      pending: 0,
      approved: 0,
      rejected: 0
    },
    
    // 加载状态
    loading: false,
    loadingText: '加载中...',
    isSwiping: false
  },
  onPullDownRefresh() {
    this.handleRefresh();
  },
  onLoad(options) {
    if (options.challengeid && options.teamid) {
      this.setData({
        challengeId: options.challengeid,
        teamId: options.teamid
      });
      this.initData();
    }
  },

  async initData() {
    await this.fetchChallengeInfo();
    await this.fetchParticipantsData();
  },

  // 第一步：获取挑战基本信息
  async fetchChallengeInfo() {
    this.setData({ loading: true, loadingText: '加载挑战详情...' });
    
    try {
      const res = await request({
        url: `https://${apiDomain}/api/challenges/${this.data.challengeId}`,
        method: 'GET',
        header: {
          'Authorization': `Bearer ${wx.getStorageSync('token')}`
        }
      });

      if (res.code === "0" && res.data) {
        let cover = '/static/images/default-challenge-cover.png';
        if (res.data.images) {
          cover = `https://${apiDomain}${JSON.parse(res.data.images).url}`;
        }
        
        this.setData({
          challengeData: {
            title: res.data.title || '未命名挑战',
            description: res.data.description || '暂无描述',
            image: cover,
            startTime: res.data.start_time,
            endTime: res.data.end_time,
            location: res.data.location,
            needFaceVerify: res.data.need_face_verify === 1
          }
        });
      }
    } catch (error) {
      console.error('获取挑战详情失败:', error);
      wx.showToast({ title: '加载挑战详情失败', icon: 'none' });
    } finally {
      this.setData({ loading: false });
    }
  },

  // 第二步：获取参与者审核数据
  async fetchParticipantsData() {
    this.setData({ loading: true, loadingText: '加载参与者数据...' });
    
    try {
      const res = await request({
        url: `https://${apiDomain}/api/teams/${this.data.teamId}/check_user`,
        method: 'POST',
        header: {
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'application/json'
        },
        data: {
          challenge_id: parseInt(this.data.challengeId),
          need_notice: false
        }
      });

      if (res.code === "0" && res.data) {
        const processed = res.data.data.map(item => ({
          ...item,
          recordId: item.participant_record_id,
          evidenceList: this.parseEvidence(item.evidence) || [],
          currentImageIndex: 0
        }));
  
        this.setData({
          '_rawParticipants': processed,
          'challengeData.totalParticipants': processed.length
        }, () => {
          this.calculateStats(); // 计算统计
          this.applyFilter();    // 应用过滤
        });
      }
    } catch (error) {
      console.error('获取参与者数据失败:', error);
      wx.showToast({ title: '加载参与者失败', icon: 'none' });
    } finally {
      this.setData({ loading: false });
    }
  },

  // 解析证据图片
  parseEvidence(evidenceStr) {
    try {
      const evidence = JSON.parse(evidenceStr);
      const result = Array.isArray(evidence) ? evidence : [evidence];
      
      console.log(result)
      const processed = result.map(item => {
        // 示例处理逻辑 - 你可以替换这部分
        if (typeof item === 'string') {
          return item.startsWith('https') ? item : `https://${apiDomain}${item}`;
        } else if (item.url) {
          return item.url.startsWith('https') ? item.url : `https://${apiDomain}${item.url}`;
        }
        return {
          
        }
      });
      console.log('[数据处理] 证据解析成功:', processed.length, '条数据');
      console.log('[处理后的证据]', processed)
      return processed;
    } catch (e) {
      console.error('[数据处理] 证据解析失败:', evidenceStr, '错误:', e);
      return ['/assets/default-evidence.png'];
    }
  },

  // Swiper切换回调
  onSwiperChange(e) {
    if (this.data.isSwiping) return;
    
    const { recordId } = e.currentTarget.dataset;
    const current = e.detail.current;
    
    // 设置防抖锁
    this.setData({ isSwiping: true }, () => {
      console.log('[用户操作] 滑动图片:', '记录ID:', recordId, '当前索引:', current);
      
      // 使用临时变量避免直接setData大对象
      const tempParticipants = [...this.data.participants];
      const participantIndex = tempParticipants.findIndex(item => item.recordId == recordId);
      
      if (participantIndex >= 0) {
        tempParticipants[participantIndex].currentImageIndex = current;
        
        this.setData({
          participants: tempParticipants,
          [`filteredParticipants[${participantIndex}].currentImageIndex`]: current
        }, () => {
          // 释放防抖锁
          this.setData({ isSwiping: false });
        });
      } else {
        this.setData({ isSwiping: false });
      }
    });
  },

  // 筛选参与者
  filterParticipants(filterIndex) {
    const targetStatus = this.data.statusFilterMap[filterIndex];
    
    this.setData({
      filteredParticipants: this.data.participants.filter(item => 
        targetStatus === 'all' || String(item.complete_state) === targetStatus
      ),
      filterIndex
    });
  },

  // 应用过滤（无抖动关键）
  applyFilter() {
    const { filterIndex, _rawParticipants, statusFilterMap } = this.data;
    const targetStatus = statusFilterMap[filterIndex];
    
    // 保持引用稳定的过滤逻辑
    const filtered = targetStatus === 'all' 
      ? [..._rawParticipants] 
      : _rawParticipants.filter(p => String(p.complete_state) === targetStatus);
    
    this.setData({
      filteredParticipants: filtered
    });
  },

  // 标签页切换
  onTabChange(e) {
    this.setData({
      filterIndex: e.detail.index
    }, () => {
      this.applyFilter();
    });
  },
  

  // 图片预览
  previewImage(e) {
    const { urls, url } = e.currentTarget.dataset;
    console.log('[用户操作] 预览图片:', '当前URL:', url);
    wx.previewImage({
      current: url,
      urls: urls
    });
  },

  // 通过审核
  async handleApprove(e) {
    const recordId = e.currentTarget.dataset.id;
    console.log('[用户操作] 通过审核:', '记录ID:', recordId);
    await this.updateStatus(recordId, '1');
  },

  // 拒绝审核
  async handleReject(e) {
    const recordId = e.currentTarget.dataset.id;
    console.log('[用户操作] 拒绝审核:', '记录ID:', recordId);
    await this.updateStatus(recordId, '0');
  },
  getStatusTagType(status) {
    return {
      '0': 'danger',    // 待审核
      '1': 'success',   // 已通过
      '2': 'warning'    // 已拒绝
    }[String(status)] || '';
  },

   // 通过审核
  async handleApprove(e) {
    const recordId = e.currentTarget.dataset.id;
    wx.showLoading({ title: '处理中...', mask: true });
    
    try {
      await this.updateStatus(recordId, '1');
      wx.showToast({
        title: '已通过',
        icon: 'success'
      });
    } catch (error) {
      wx.showToast({
        title: '操作失败',
        icon: 'none'
      });
    } finally {
      wx.hideLoading();
    }
  },

  // 拒绝审核
  async handleReject(e) {
    const recordId = e.currentTarget.dataset.id;
    wx.showLoading({ title: '处理中...', mask: true });
    
    try {
      await this.updateStatus(recordId, '2');
      wx.showToast({
        title: '已拒绝',
        icon: 'success'
      });
    } catch (error) {
      wx.showToast({
        title: '操作失败',
        icon: 'none'
      });
    } finally {
      wx.hideLoading();
    }
  },

  // 更新状态（核心方法）
  async updateStatus(recordId, status) {
    try {
      wx.showLoading({ title: '处理中...', mask: true });
      
      // 1. 调用API更新状态
      const res = await request({
        url: `https://${apiDomain}/api/teams/${recordId}/modify`,
        method: 'POST',
        header: {
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'application/json'
        },
        data: { complete_state: status }
      });
  
      if (res.code !== "200") {
        throw new Error(res.msg || '操作失败');
      }
  
      // 2. 立即更新本地UI（优化体验）
      const tempParticipants = [...this.data._rawParticipants];
      const index = tempParticipants.findIndex(item => item.recordId === recordId);
      
      if (index >= 0) {
        tempParticipants[index].complete_state = status;
        
        this.setData({
          '_rawParticipants': tempParticipants,
          [`filteredParticipants[${index}].complete_state`]: status
        }, () => {
          // 3. 重新计算统计数字
          this.calculateStats();
        });
      }
  
      // 4. 刷新完整数据（确保与服务器一致）
      await this.refreshData();
      
      wx.showToast({
        title: status === '1' ? '已通过' : '已拒绝',
        icon: 'success'
      });
    } catch (error) {
      console.error('状态更新失败:', error);
      wx.showToast({
        title: '操作失败: ' + error.message,
        icon: 'none'
      });
    } finally {
      wx.hideLoading();
    }
  },
    // 单独提取统计计算逻辑
  calculateStats() {
    const participants = this.data._rawParticipants;
    
    this.setData({
      'stats.total': participants.length,
      'stats.pending': participants.filter(p => p.complete_state === '0').length,
      'stats.approved': participants.filter(p => p.complete_state === '1').length,
      'stats.rejected': participants.filter(p => p.complete_state === '2').length
    });
  },
  
  // 获取状态文本
  getStatusText(status) {
    return {
      '0': '待审核',
      '1': '已通过', 
      '2': '已拒绝'
    }[String(status)] || '';
  },
  // 更新审核状态
  async updateStatus(recordId, status) {
    try {
      const res = await request({
        url: `https://${apiDomain}/api/teams/${recordId}/modify`,
        method: 'POST',
        header: {
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'application/json'
        },
        data: { complete_state: status }
      });

      if (res.code === "200") {
        const newParticipants = this.data._rawParticipants.map(item => 
          item.recordId === recordId ? { ...item, complete_state: status } : item
        );
        
        // 更新数据并重新计算统计
        this.setData({
          '_rawParticipants': newParticipants,
          'stats.pending': newParticipants.filter(p => p.complete_state === '0').length,
          'stats.approved': newParticipants.filter(p => p.complete_state === '1').length,
          'stats.rejected': newParticipants.filter(p => p.complete_state === '2').length
        }, () => {
          this.applyFilter(); // 重新应用当前过滤
          wx.showToast({
            title: status === '1' ? '已通过' : '已拒绝',
            icon: 'success'
          });
        });
      }
    } catch (error) {
      wx.showToast({ title: '操作失败', icon: 'none' });
    }
  },

  // 返回
  onClickLeft() {
    console.log('[用户操作] 点击返回按钮');
    wx.navigateBack();
  },
  async refreshData() {
    try {
      // 同时刷新挑战信息和参与者数据
      await Promise.all([
        this.fetchChallengeInfo(),
        this.fetchParticipantsData()
      ]);
      
      wx.showToast({
        title: '刷新成功',
        icon: 'success'
      });
    } catch (error) {
      console.error('刷新数据失败:', error);
      throw error; // 抛出错误给上层处理
    }
  },
  // 统一处理刷新逻辑
  async handleRefresh() {
    if (this.data.isRefreshing) return;
    
    this.setData({ isRefreshing: true });
    wx.showNavigationBarLoading(); // 导航条加载动画
    
    try {
      await this.refreshData();
    } catch (error) {
      console.error('下拉刷新失败:', error);
      wx.showToast({
        title: '刷新失败',
        icon: 'none'
      });
    } finally {
      this.setData({ isRefreshing: false });
      wx.stopPullDownRefresh(); // 停止下拉刷新动画
      wx.hideNavigationBarLoading(); // 隐藏导航条加载动画
    }
  },
})