const { apiDomain } = require("../../../../config");

Page({
  data: {
    id: '',
    currentTime: '',
    challenge: {
      title: '',
      description: '',
      images: '',
      object_type: '',
      gesture_type: '',
      landmark_name: '',
      radius: 100,
      need_face_verify: 0,
      create_time: '',
      start_time: '',
      end_time: '',
      status: 'ongoing',
      location: null,
      statistics: {
        participants: 0,
        completion_rate: 0
      },
      leaderboard: []
    },
    creatorInfo: {
      nickname: '',
      avatar: ''
    },
    participants: [],
    isJoined: false,
    remainTimeText: '',
    formattedTimes: {
      createTime: '',
      startTime: '',
      endTime: ''
    }
  },

  onLoad(options) {
    if (options.id) {
      this.setData({ id: options.id });
      this.loadData();
    } else {
      wx.showToast({ title: '参数错误', icon: 'none' });
      setTimeout(() => wx.navigateBack(), 1500);
    }
    
    // 初始化时间
    this.updateCurrentTime();
    this.timer = setInterval(() => {
      this.updateCurrentTime();
      this.updateRemainTime();
    }, 60000);
  },

  onUnload() {
    clearInterval(this.timer);
  },

  async loadData() {
    wx.showLoading({ title: '加载中...' });
    
    try {
      console.group('---- 开始加载挑战详情数据 ----');
      
      // 1. 获取挑战详情
      console.log('[DEBUG] 正在请求挑战详情，ID:', this.data.id);
      const challengeRes = await this.requestChallengeDetail();
      console.log('[DEBUG] 挑战详情原始数据:', JSON.stringify(challengeRes, null, 2));
      
      // 2. 获取创建者信息
      if (challengeRes.creator_id) {
        console.log('[DEBUG] 正在请求创建者信息，用户ID:', challengeRes.creator_id);
        const creatorRes = await this.requestUserInfo(challengeRes.creator_id);
        console.log('[DEBUG] 创建者原始数据:', JSON.stringify(creatorRes, null, 2));
        
        this.setData({ 
          creatorInfo: {
            nickname: creatorRes.account || '匿名用户',
            avatar: creatorRes.avatar || '/assets/default-avatar.jpg',
            rawData: creatorRes // 保留原始数据用于调试
          }
        });
      } else {
        console.warn('[WARN] 挑战数据中没有creator_id字段');
      }
      
      // 4. 处理并设置数据
      const processedChallenge = {
        ...challengeRes,
        status: this.calculateChallengeStatus(challengeRes.end_time),
        rawData: challengeRes // 保留原始数据
      };
      
      console.log('[DEBUG] 处理后挑战数据:', JSON.stringify(processedChallenge, null, 2));
      
      this.updateRemainTime();
      // 添加定时更新
      this.remainTimer = setInterval(() => this.updateRemainTime(), 60000);
      
      this.setData({
        challenge: processedChallenge,
        isJoined: this.checkIsJoined(challengeRes.id),
        formattedTimes: {
          createTime: this.formatDate(challengeRes.create_time),
          startTime: this.formatDateTime(challengeRes.start_time),
          endTime: this.formatDateTime(challengeRes.end_time)
        }
      });
      
      // 5. 更新时间显示
      this.updateRemainTime();
      console.log('[DEBUG] 数据加载完成，当前页面数据:', JSON.stringify(this.data, null, 2));
      
    } catch (error) {
      console.error('[ERROR] 数据加载失败:', error);
      wx.showToast({ 
        title: '加载失败', 
        icon: 'none',
        duration: 3000
      });
    } finally {
      console.groupEnd();
      wx.hideLoading();
    }
  },

  // 请求挑战详情
  requestChallengeDetail() {
    return new Promise((resolve, reject) => {
      wx.request({
        url: `https://${apiDomain}/api/challenges/${this.data.id}`,
        method: 'GET',
        header: { 'Authorization': `Bearer ${wx.getStorageSync('token')}` },
        success: (res) => {
          if (res.data.code === "200" || res.data.code === "0") {
            console.log('[接口返回信息]', res.data.data)
            const data = res.data.data
            if (data.images && data.images != '{}') {
              console.log('封面不为空')
              data.images = `https://${apiDomain}${JSON.parse(data.images).url}`
            }else{
              data.images = '/static/images/default-challenge-cover.jpg'
            }
            
            resolve(data);
          } else {
            reject(new Error(res.data.msg || '获取详情失败'));
          }
        },
        fail: reject
      });
    });
  },

  // 请求用户信息
  requestUserInfo(userId) {
    return new Promise((resolve, reject) => {
      console.log(`[NETWORK] 正在请求用户信息 API: /api/users/${userId}`);
      
      wx.request({
        url: `https://${apiDomain}/api/users/${userId}`,
        method: 'GET',
        header: { 
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'X-Debug': 'true' // 添加调试标记
        },
        success: (res) => {
          console.log(`[NETWORK] 用户API响应状态: ${res.statusCode}`);
          console.log('[NETWORK] 响应头:', res.header);
          
          if (res.data.code === "200" || res.data.code === '0') {
            console.log('[DEBUG] 用户数据响应体:', res.data);
            resolve(res.data.data || {});
          } else {
            console.error('[API ERROR] 用户接口返回错误:', res.data);
            reject(new Error(res.data.msg || '获取用户信息失败'));
          }
        },
        fail: (err) => {
          console.error('[NETWORK ERROR] 用户请求失败:', err);
          reject(new Error('网络请求失败'));
        }
      });
    });
  },

  // 检查是否已参加
  checkIsJoined(challengeId) {
    const joinedChallenges = wx.getStorageSync('joinedChallenges') || [];
    return joinedChallenges.includes(challengeId);
  },

  // 计算挑战状态
  calculateChallengeStatus(endTime) {
    if (!endTime) return 'ongoing';
    const now = new Date();
    const end = new Date(endTime);
    return now > end ? 'ended' : 'ongoing';
  },

  // 更新时间显示
  updateCurrentTime() {
    const now = new Date();
    this.setData({
      currentTime: `${now.getHours().toString().padStart(2, '0')}:${now.getMinutes().toString().padStart(2, '0')}`
    });
  },

  // 增强的剩余时间计算方法
  updateRemainTime() {
    if (!this.data.challenge.end_time) {
      this.setData({ remainTimeText: '长期有效' });
      return;
    }
    
    const endDate = new Date(this.data.challenge.end_time);
    const now = new Date();
    const diffMs = endDate - now;
    
    // 已结束的情况
    if (diffMs <= 0) {
      this.setData({ 
        remainTimeText: '已结束',
        'challenge.status': 'ended' 
      });
      return;
    }
    
    // 计算时间差
    const diffDays = Math.floor(diffMs / (1000 * 60 * 60 * 24));
    const diffHours = Math.floor((diffMs % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
    const diffMinutes = Math.floor((diffMs % (1000 * 60 * 60)) / (1000 * 60));
    
    // 生成友好提示
    let text = '';
    if (diffDays > 30) {
      const months = Math.floor(diffDays / 30);
      text = `${months}个月后结束`;
    } else if (diffDays > 7) {
      text = `${diffDays}天后结束`;
    } else if (diffDays > 0) {
      text = `${diffDays}天${diffHours}小时后结束`;
    } else if (diffHours > 0) {
      text = `${diffHours}小时${diffMinutes}分钟后结束`;
    } else {
      text = `${diffMinutes}分钟后结束`;
    }
    
    this.setData({ 
      remainTimeText: text,
      'challenge.status': 'ongoing'
    });
  },

  // 修改后的格式化方法
  formatDate(dateStr) {
    if (!dateStr) return '未知时间';
    try {
      const date = new Date(dateStr);
      if (isNaN(date.getTime())) return '未知时间';
      
      const year = date.getFullYear();
      const month = (date.getMonth() + 1).toString().padStart(2, '0');
      const day = date.getDate().toString().padStart(2, '0');
      
      return `${year}-${month}-${day}`;
    } catch (e) {
      console.error('日期格式化失败:', e);
      return '未知时间';
    }
  },

  formatDateTime(dateStr) {
    if (!dateStr) return '未知时间';
    try {
      const date = new Date(dateStr);
      if (isNaN(date.getTime())) return '未知时间';
      
      const year = date.getFullYear();
      const month = (date.getMonth() + 1).toString().padStart(2, '0');
      const day = date.getDate().toString().padStart(2, '0');
      const hours = date.getHours().toString().padStart(2, '0');
      const minutes = date.getMinutes().toString().padStart(2, '0');
      
      return `${year}-${month}-${day} ${hours}:${minutes}`;
    } catch (e) {
      console.error('日期时间格式化失败:', e);
      return '未知时间';
    }
  },

  // 显示地图
  showLocationMap() {
    const { location } = this.data.challenge;
    if (!location) {
      return wx.showToast({ title: '无位置信息', icon: 'none' });
    }
    
    wx.openLocation({
      latitude: location.lat,
      longitude: location.lng,
      name: this.data.challenge.landmark_name || this.data.challenge.title,
      scale: 18
    });
  },

  // 处理参加
  handleJoin() {
    if (this.data.isJoined) return;
    
    wx.showModal({
      title: '确认参与',
      content: `确定要参加"${this.data.challenge.title}"挑战吗？`,
      success: (res) => {
        if (res.confirm) {
          this.joinChallenge();
        }
      }
    });
  },

  // 参加挑战
  // 参加挑战
  async joinChallenge() {
    
    if (this.data.challenge.need_face_verify) {
      const token = wx.getStorageSync('token');
    
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/flask/api/face/check_registered`, 
          method: 'POST',
          header: {
            'Authorization': token
          },
          success: (res) => resolve(res.data),
          fail: reject
        });
      });
      console.log('[检测注册接口响应]', res)
      if (res.code !== 0) {
        const modalRes = await new Promise((resolve, reject) => {
          wx.showModal({
            title: '人脸验证',
            content: '参加该挑战需要人脸认证才可参与，需要前往注册吗？',
            success: resolve,
            fail: reject
          });
        });
    
        if (modalRes.confirm) {
          wx.navigateTo({
            url: '/pages/my/edit_profile/edit_profile',
          });
          return; // 避免继续执行下面的逻辑
        } else {
          return; // 用户取消，也提前结束流程
        }
      }
    }
    try {
      wx.showLoading({ title: '处理中...' });
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/challenges/${this.data.id}/join`,
          method: 'POST',
          header: { 'Authorization': `Bearer ${wx.getStorageSync('token')}` },
          success: resolve,
          fail: reject
        });
      });
      
      console.log("=========", res.data)
      // 成功或已参与都视为"成功状态"
      if (res.data.code === "200" || res.data.code === "0" || 
          res.data.msg?.includes("已加入")) {
        this.setData({ isJoined: true });
        wx.hideLoading();
        this.showSubmitDialog(res.data.msg?.includes("已加入"));
      } else {
        throw new Error(res.data.msg || '参与失败');
      }
    } catch (error) {
      console.error('参与挑战失败:', error);
      wx.hideLoading();
      
      // 特殊处理"已加入"的错误
      if (error.message.includes("已加入")) {
        this.setData({ isJoined: true });
        this.showSubmitDialog(true);
      } else {
        wx.showToast({ 
          title: error.message, 
          icon: 'none',
          duration: 2000
        });
      }
    }
  },

// 新增：统一弹窗方法
/**
 * 显示挑战提交对话框
 * @param {boolean} isAlreadyJoined - 用户是否已经参与过该挑战
 * @description 根据用户是否已参与过挑战显示不同的对话框内容，
 * 提供用户选择立即提交或稍后处理的选项。
 * 确认后跳转到挑战提交页面，取消则显示相应提示。
 */
showSubmitDialog(isAlreadyJoined = false) {
  wx.showModal({
    title: isAlreadyJoined ? '您已参与过该挑战' : '参与成功',
    content: isAlreadyJoined ? 
      '是否跳转到挑战提交页面更新您的参与记录？' :
      '是否立即跳转到挑战信息提交页面？\n(稍后可在"我的→我的挑战"中提交)',
    confirmText: '立即提交',
    cancelText: '稍后处理',
    success: (res) => {
      if (res.confirm) {
        // 跳转到提交页面
        wx.navigateTo({
          url: `/pages/interaction/challenge/challenge_submit/challenge_submit?challengeId=${this.data.id}`,
          success: () => {
            console.log('跳转到提交页面成功');
          },
          fail: (err) => {
            console.error('跳转失败:', err);
            wx.showToast({
              title: '跳转失败，请稍后手动提交',
              icon: 'none'
            });
          }
        });
      } else {
        wx.showToast({
          title: isAlreadyJoined ? 
            '您可以在"我的挑战"页面查看' : 
            '已保存至我的挑战',
          icon: 'none',
          duration: 1500
        });
      }
    }
  });
},

  // 返回
  navigateBack() {
    wx.navigateBack();
  }
});