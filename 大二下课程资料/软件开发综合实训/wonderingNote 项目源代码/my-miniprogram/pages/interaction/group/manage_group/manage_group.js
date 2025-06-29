const { apiDomain } = require("../../../../config");

// 封装wx.request为Promise
function request(options) {
  return new Promise((resolve, reject) => {
    wx.request({
      ...options,
      success: (res) => {
        if (res.statusCode >= 200 && res.statusCode < 300) {
          resolve(res);
        } else {
          reject(res);
        }
      },
      fail: (err) => {
        reject(err);
      }
    });
  });
}

Page({
  data: {
    groupId: '',
    groupName: '',
    isCreator: false,
    menuVisibleIndex: -1,
    showInvitePopup: false,
    showSearchDialog: false,
    searchValue: '',
    members: [],
    loading: false,
    hasMore: true,
    lastCursor: '0',
    pageSize: 10,
    searchedUser: null,
    showSearchResult: false,

  },

  onLoad(options) {
    if (options.id) {
      this.setData({ 
        groupId: options.id,
        groupName: options.name || ''
      });
      this.fetchMembers(true);
    }
  },

  formatTime(dateString) {
    if (!dateString) return '';
    const date = new Date(dateString);
    if (isNaN(date.getTime())) return '';
    
    const now = new Date();
    const diffInSeconds = Math.floor((now - date) / 1000);
    
    if (diffInSeconds < 60) return '刚刚';
    if (diffInSeconds < 3600) return `${Math.floor(diffInSeconds / 60)}分钟前`;
    if (diffInSeconds < 86400) return `${Math.floor(diffInSeconds / 3600)}小时前`;
    if (diffInSeconds < 2592000) return `${Math.floor(diffInSeconds / 86400)}天前`;
    
    const year = date.getFullYear();
    const month = date.getMonth() + 1;
    const day = date.getDate();
    return `${year}-${month < 10 ? '0' + month : month}-${day < 10 ? '0' + day : day}`;
  },

  async fetchMembers(initialLoad = false) {
    if (this.data.loading || !this.data.hasMore) {
      console.log('fetchMembers: 正在加载或无更多数据，取消请求');
      return;
    }
    
    this.setData({ loading: true });
    const token = wx.getStorageSync('token');
    
    try {
      const queryParams = [
        `size=${this.data.pageSize}`,
        ...(this.data.lastCursor ? [`lastCursor=${this.data.lastCursor}`] : [])
      ].join('&');
      
      const url = `https://${apiDomain}/api/teams/${this.data.groupId}/members?${queryParams}`;
      console.log('fetchMembers: 请求URL:', url);
  
      const res = await request({
        url,
        method: 'GET',
        header: { 'Authorization': `Bearer ${token}` }
      });
  
      console.log('fetchMembers: 接口响应:', res);
      
      if (res.statusCode === 200 && res.data.code === '0') {
        // 根据实际返回数据结构调整
        const responseData = res.data.data;
        const membersData = responseData.data || [];
        
        // 处理头像URL
        const newMembers = membersData.map(member => {
          let avatarUrl = '/static/images/default-avatar.jpg';
          try {
            if (member.user_avatar) {
              const avatarObj = JSON.parse(member.user_avatar);
              avatarUrl = `https://${apiDomain}${avatarObj.url}`
            }
          } catch (e) {
            console.warn('解析头像数据失败:', member.user_avatar);
          }
          console.log(avatarUrl)
          return {
            id: member.id,
            user_account: member.user_account,
            user_avatar: avatarUrl,
            join_time: this.formatTime(member.join_time),
            update_time: member.update_time,
            is_admin: member.is_admin || false
          };
        });
  
        console.log('fetchMembers: 处理后的成员数据:', newMembers);
        
        this.setData({
          members: initialLoad ? newMembers : [...this.data.members, ...newMembers],
          lastCursor: responseData.nextCursor || null,
          hasMore: !!responseData.nextCursor,
          // 注意：实际接口返回中未看到is_creator字段，可能需要从其他接口获取
          isCreator: false // 暂时设为false，需要根据实际业务调整
        });
        console.log(this.data.members)
  
      } else {
        throw new Error(res.data?.msg || `请求失败，状态码: ${res.statusCode}`);
      }
    } catch (error) {
      console.error('fetchMembers: 获取成员列表出错:', error);
      wx.showToast({ 
        title: '加载成员列表失败，请稍后重试', 
        icon: 'none',
        duration: 2000
      });
      
      if (initialLoad) {
        this.setData({
          members: [],
          hasMore: false
        });
      }
    } finally {
      this.setData({ loading: false });
    }
  },

  loadMoreMembers() {
    if (!this.data.loading && this.data.hasMore) {
      this.fetchMembers();
    }
  },

  toggleMenu(e) {
    const index = e.currentTarget.dataset.index;
    this.setData({
      menuVisibleIndex: this.data.menuVisibleIndex === index ? -1 : index
    });
  },

  showInvitePopup() {
    this.setData({ showInvitePopup: true });
  },

  onCloseInvite() {
    this.setData({ showInvitePopup: false });
  },

  onShareWechat() {
    wx.showShareMenu({
      withShareTicket: true,
      menus: ['shareAppMessage']
    });
    wx.showToast({
      title: '请点击右上角转发',
      icon: 'none'
    });
    this.setData({ showInvitePopup: false });
  },

  onSearchUser() {
    this.setData({
      showInvitePopup: false,
      showSearchDialog: true
    });
  },

  async onCopyLink() {
    const token = wx.getStorageSync('token');
    wx.showLoading({ title: '生成链接中...' });

    try {
      const res = await request({
        url: `https://${apiDomain}/api/teams/${this.data.groupId}/invite`,
        method: 'POST',
        header: { 'Authorization': `Bearer ${token}` }
      });

      if (res.data.code === '0') {
        const inviteUrl = `https://${apiDomain}/invite/${res.data.data.invite_id}`;
        wx.setClipboardData({
          data: inviteUrl,
          success: () => {
            wx.showToast({
              title: '邀请链接已复制',
              icon: 'success'
            });
          }
        });
      } else {
        throw new Error(res.data?.msg || '生成链接失败');
      }
    } catch (error) {
      console.error('生成邀请链接出错:', error);
      wx.showToast({
        title: error.message || '操作失败',
        icon: 'none'
      });
    } finally {
      wx.hideLoading();
      this.setData({ showInvitePopup: false });
    }
  },

  onSearchInput(e) {
    this.setData({ searchValue: e.detail.value });
  },

  async onSearch() {
    if (!this.data.searchValue.trim()) {
      wx.showToast({ title: '请输入邮箱', icon: 'none' });
      return;
    }
  
    if (!this.validateEmail(this.data.searchValue)) {
      wx.showToast({ title: '请输入有效的邮箱地址', icon: 'none' });
      return;
    }
  
    wx.showLoading({ title: '搜索中...' });
    const token = wx.getStorageSync('token');
  
    try {
      console.log('准备发送搜索请求', {
        email: this.data.searchValue,
        token: token ? '已设置' : '未设置'
      });
  
      const res = await request({
        url: `https://${apiDomain}/api/hall/users/search`,
        method: 'POST',
        header: { 
          'Authorization': `Bearer ${token}`,
          'Content-Type': 'application/json'
        },
        data: { 
          'email': this.data.searchValue
        }
      });
  
      console.log('搜索响应', {
        status: res.statusCode,
        data: res.data
      });
  
      if (res.statusCode === 200 && res.data.code === '0') {
        // 修改这里 - 不再检查数组长度，直接使用返回的用户对象
        if (res.data.data) {  // 直接检查data是否存在
          const user = res.data.data;  // 直接使用返回的对象
          this.setData({
            searchedUser: {
              id: user.id,
              account: user.user_account,
              avatar: this.processAvatarUrl(user.avatar),
              email: user.email
            },
            showSearchResult: true
          });
        } else {
          wx.showToast({ title: '未找到该邮箱用户', icon: 'none' });
        }
      } else {
        throw new Error(res.data?.msg || '搜索失败');
      }
    } catch (error) {
      console.error('搜索用户失败', error);
      wx.showToast({
        title: error.message || '搜索失败',
        icon: 'none'
      });
    } finally {
      wx.hideLoading();
      this.setData({
        showSearchDialog: false,
        searchValue: ''
      });
    }
  },
  
  // 辅助方法
  validateEmail(email) {
    const re = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return re.test(email);
  },
  
  processAvatarUrl(originAvatar) {
    let avatar = '/static/images/default-avatar.jpg'
    if (originAvatar && originAvatar != '{}') {
      avatar = `https://${apiDomain}${JSON.parse(originAvatar).url}`
    }
    return avatar
  },

closeSearchResult() {
  this.setData({
    showSearchResult: false,
    searchedUser: null
  });
},
// 新增的邀请用户方法
async inviteUser() {
  if (!this.data.searchedUser) return;
  
  wx.showLoading({ title: '邀请中...' });
  const token = wx.getStorageSync('token');

  try {
    const res = await request({
      url: `https://${apiDomain}/api/teams/${this.data.groupId}/invite`,
      method: 'POST',
      header: { 
        'Authorization': `Bearer ${token}`,
        'Content-Type': 'application/json'
      },
      data: {
        userId: this.data.searchedUser.id
      }
    });

    if (res.data.code === '0') {
      // 先显示成功提示
      wx.showToast({
        title: '邀请成功',
        icon: 'success'
      });
      
      // 延迟500ms后刷新列表，确保用户看到提示
      setTimeout(() => {
        this.fetchMembers(true);
      }, 500);
      
    } else {
      throw new Error(res.data?.msg || '邀请失败');
    }
  } catch (error) {
    console.error('邀请用户出错:', error);
    wx.showToast({
      title: error.message || '邀请失败',
      icon: 'none'
    });
  } finally {
    // 不再在这里关闭loading，让fetchMembers完成后自动处理
    this.setData({
      showSearchResult: false,
      searchedUser: null
    });
  }
},


  handleSearchResult(users) {
    if (users && users.length > 0) {
      wx.navigateTo({
        url: `/pages/user/search_result?users=${JSON.stringify(users)}&groupId=${this.data.groupId}`
      });
    } else {
      wx.showToast({ title: '未找到相关用户', icon: 'none' });
    }
  },

  onCloseSearch() {
    this.setData({
      showSearchDialog: false,
      searchValue: ''
    });
  },

  onView(e) {
    const userId = e.currentTarget.dataset.id;
    wx.navigateTo({
      url: `/pages/interaction/user_profile/user_profile?id=${userId}`
    });
  },

  async onDelete(e) {
    const userId = e.currentTarget.dataset.id;
    const res = await wx.showModal({
      title: '确认移除',
      content: '确定要将该成员移出群组吗？'
    });

    if (res.confirm) {
      const token = wx.getStorageSync('token');
      wx.showLoading({ title: '处理中...' });

      try {
        const res = await request({
          url: `https://${apiDomain}/api/teams/${this.data.groupId}/members`,
          method: 'DELETE',
          header: {
            'Authorization': `Bearer ${token}`,
            'Content-Type': 'application/json'
          },
          data: {
            user_id: userId  // ⬅️ 注意：放在 body 中！
          }
        });

        if (res.data.code === '0') {
          this.setData({
            members: this.data.members.filter(m => m.id !== userId),
            menuVisibleIndex: -1
          });
          wx.showToast({
            title: '已移除成员',
            icon: 'success'
          });
        } else {
          throw new Error(res.data?.msg || '移除失败');
        }
      } catch (error) {
        console.error('移除成员出错:', error);
        wx.showToast({
          title: error.message || '移除失败',
          icon: 'none'
        });
      } finally {
        wx.hideLoading();
      }
    }
  },
  /**
   * 带下拉动画的刷新
   */
  onPullDownRefresh() {
    wx.showNavigationBarLoading(); // 显示导航栏加载动画
    
    this.setData({
      currentPage: 1,
      lastCursor: '0',
      hasMore: true,
      members: []
    }, async () => {
      try {
        await this.fetchMembers(true);
        wx.stopPullDownRefresh();
      } catch (error) {
        wx.stopPullDownRefresh();
        wx.showToast({ title: '刷新失败', icon: 'none' });
      } finally {
        wx.hideNavigationBarLoading();
      }
    });
  },
  
  // 显示挑战弹窗
  async showGroupChallenges() {
    this.setData({ 
      showChallengesPopup: true,
      groupChallenges: [],
      challengesLastCursor: '0',
      challengesHasMore: true
    });
    this.fetchGroupChallenges(true);
  },

  // 关闭弹窗
  closeChallengesPopup() {
    this.setData({ showChallengesPopup: false });
  },

  // 获取群组挑战
  async fetchGroupChallenges(initialLoad = false) {
    if (this.data.challengesLoading || !this.data.challengesHasMore) return;
    
    this.setData({ challengesLoading: true });
    const token = wx.getStorageSync('token');
    
    try {
      const queryParams = [
        `size=10`,
        ...(this.data.challengesLastCursor ? [`lastCursor=${this.data.challengesLastCursor}`] : [])
      ].join('&');
      
      const res = await request({
        url: `https://${apiDomain}/api/teams/${this.data.groupId}/challenge_info?${queryParams}`,
        method: 'GET',
        header: { 'Authorization': `Bearer ${token}` }
      });

      if (res.statusCode === 200 && res.data.code === '0') {
        const responseData = res.data.data;
        const challenges = (responseData.data || []).map(challenge => {
          // 处理封面图片
          let coverUrl = '/images/default-challenge.png';
          try {
            if (challenge.cover && typeof challenge.cover === 'string') {
              const coverObj = JSON.parse(challenge.cover);
              coverUrl = `https://${apiDomain}${coverObj.url}`;
            }
          } catch (e) {
            console.error('封面解析失败:', challenge.cover, e);
          }

          return {
            ...challenge,
            cover: coverUrl,
            formatted_end_time: this.formatChallengeTime(challenge.end_time)
          };
        });

        console.log('处理后的挑战数据:', challenges);
        
        this.setData({
          groupChallenges: initialLoad ? 
            challenges : [...this.data.groupChallenges, ...challenges],
          challengesLastCursor: responseData.nextCursor || '0',
          challengesHasMore: !!responseData.nextCursor
        });
      } else {
        throw new Error(res.data?.msg || '获取挑战失败');
      }
    } catch (error) {
      console.error('获取群组挑战失败:', error);
      wx.showToast({
        title: error.message || '获取挑战失败',
        icon: 'none'
      });
    } finally {
      this.setData({ challengesLoading: false });
    }
  },

  // 格式化挑战时间
  formatChallengeTime(endTime) {
    if (!endTime) return '无截止时间';
    const date = new Date(endTime);
    return `${date.getFullYear()}-${(date.getMonth()+1).toString().padStart(2,'0')}-${date.getDate().toString().padStart(2,'0')}`;
  },

  // 提醒特定挑战
  async remindChallenge(e) {
    const challengeId = e.currentTarget.dataset.id;
    const res = await wx.showModal({
      title: '确认提醒',
      content: '确定要通知群成员参与此挑战吗？'
    });
    
    if (!res.confirm) return;

    wx.showLoading({ title: '发送通知中...' });
    const token = wx.getStorageSync('token');
    
    try {
      const remindRes = await request({
        url: `https://${apiDomain}/api/teams/${this.data.groupId}/post_inv`,
        method: 'POST',
        header: {
          'Authorization': `Bearer ${token}`,
          'Content-Type': 'application/json'
        },
        data: {
          challenge_id: challengeId
        }
      });

      if (remindRes.data.code === '0') {
        wx.showToast({
          title: '通知已发送',
          icon: 'success'
        });
      } else {
        throw new Error(remindRes.data?.msg || '通知失败');
      }
    } catch (error) {
      console.error('发送挑战通知失败:', error);
      wx.showToast({
        title: error.message || '通知失败',
        icon: 'none'
      });
    } finally {
      wx.hideLoading();
    }
  },
  navigateBack() {
    wx.navigateBack();
  }
});