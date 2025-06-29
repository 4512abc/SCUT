const { apiDomain } = require('../../../config');

Page({
  data: {
    createdGroups: [],
    joinedGroups: [],
    loading: false,
    createdHasMore: true,
    joinedHasMore: true,
    createdLastCursor: '0',
    joinedLastCursor: '0',
    pageSize: 10,
    activeTab: 0, // 0-我加入的 1-我创建的
    isRefreshing: false,
    showChallengePopup: false,
    currentGroupChallenges: [],
    currentGroupId: null,
    currentGroupChallengeCursor: '0'
  },

  onLoad() {
    this.loadData();
  },

  onShow() {
  },

  loadData() {
    if (this.data.activeTab === 0) {
      this.fetchJoinedGroups();
    } else {
      this.fetchCreatedGroups();
    }
  },

  refreshData() {
    this.setData({
      createdGroups: [],
      joinedGroups: [],
      createdLastCursor: '0',
      joinedLastCursor: '0',
      createdHasMore: true,
      joinedHasMore: true,
      loading: true
    }, () => {
      this.loadData();
    });
  },

  onTabChange(e) {
    const { index } = e.detail;
    this.setData({ activeTab: index }, () => {
      if ((index === 0 && this.data.joinedGroups.length === 0) || 
          (index === 1 && this.data.createdGroups.length === 0)) {
        this.loadData();
      }
    });
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

  async fetchCreatedGroups() {
    if (this.data.loading || !this.data.createdHasMore) return;
    
    this.setData({ loading: true });
    const token = wx.getStorageSync('token');
    
    try {
      const queryParams = [
        `size=${this.data.pageSize}`,
        ...(this.data.createdLastCursor ? [`lastCursor=${this.data.createdLastCursor}`] : [])
      ].join('&');
      
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/auth/team_info?${queryParams}`,
          method: 'GET',
          header: { 'Authorization': token },
          success: resolve,
          fail: reject
        });
      });
      console.log('[我创建的群组接口响应]', res)
      if (res.statusCode === 200 && res.data.code === '0') {
        const newGroups = res.data.data.data || [];
        
        this.setData({
          createdGroups: [...this.data.createdGroups, ...newGroups.map(group => {
            let logo = `https://${apiDomain}${JSON.parse(group.logo).url}`
            return{
            ...group,
            updateTime: this.formatTime(group.create_time),
            maxMember: group.max_members || 0,
            logo: logo || null
            }
          })],
          createdLastCursor: res.data.data.nextCursor || '0',
          createdHasMore: !!res.data.data.nextCursor,
          isRefreshing: false
        });
      } else {
        throw new Error(res.data?.msg || '获取创建的群组失败');
      }
    } catch (error) {
      console.error('获取创建的群组出错:', error);
      wx.showToast({ 
        title: error.message || '加载失败', 
        icon: 'none' 
      });
    } finally {
      this.setData({ loading: false });
    }
  },

  async fetchJoinedGroups() {
    if (this.data.loading || !this.data.joinedHasMore) return;
    
    this.setData({ loading: true });
    const token = wx.getStorageSync('token');
    console.log(token)
    try {
      const queryParams = [
        `size=${this.data.pageSize}`,
        ...(this.data.joinedLastCursor ? [`lastCursor=${this.data.joinedLastCursor}`] : [])
      ].join('&');
      
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/auth/team_join?${queryParams}`,
          method: 'GET',
          header: { 'Authorization': token },
          success: resolve,
          fail: reject
        });
      });
      console.log('[我加入的群组接口响应]', res)
      if (res.statusCode === 200 && res.data.code === '0') {
        const newGroups = res.data.data.data || [];
        this.setData({
          joinedGroups: [...this.data.joinedGroups, ...newGroups.map(group => {
            const logo = `https://${apiDomain}${JSON.parse(group.logo).url}`
            return {
            ...group,
            updateTime: this.formatTime(group.create_time),
            maxMember: group.max_members || 0,
            logo: logo || null
            }
          })].reverse(),
          joinedLastCursor: res.data.data.nextCursor || '0',
          joinedHasMore: !!res.data.data.nextCursor,
          isRefreshing: false
        });
      } else {
        throw new Error(res.data?.msg || '获取加入的群组失败');
      }
    } catch (error) {
      console.error('获取加入的群组出错:', error);
      wx.showToast({ 
        title: error.message || '加载失败', 
        icon: 'none' 
      });
    } finally {
      this.setData({ loading: false });
    }
  },

  navigateBack() {
    wx.navigateBack();
  },

  navigateToCreateGroup() {
    wx.navigateTo({
      url: '/pages/interaction/group/group_create/group_create',
      success: () => {
        this.setData({ needRefresh: true });
      }
    });
  },

  navigatoToManageGroup(e) {
    const { id } = e.currentTarget.dataset;
    wx.navigateTo({
      url: `/pages/interaction/group/manage_group/manage_group?id=${id}`,
      success: () => {
        this.setData({ needRefresh: true });
      }
    });
  },

  onPullDownRefresh() {
    this.setData({ isRefreshing: true });
    this.refreshData();
    wx.stopPullDownRefresh();
  },

  onReachBottom() {
    if (this.data.activeTab === 0) {
      this.fetchJoinedGroups();
    } else {
      this.fetchCreatedGroups();
    }
  },
  // 显示群组挑战弹窗
  async showChallenges(e) {
    const groupId = e.currentTarget.dataset.id;
    this.setData({ 
      loading: true,
      currentGroupId: groupId
    });
    
    try {
      const challenges = await this.fetchGroupChallenges(groupId);
      this.setData({
        currentGroupChallenges: challenges,
        showChallengePopup: true
      });
    } catch (error) {
      wx.showToast({
        title: '获取挑战失败',
        icon: 'none'
      });
    } finally {
      this.setData({ loading: false });
    }
  },

  // 关闭弹窗
  closeChallengePopup() {
    this.setData({ showChallengePopup: false });
  },

  // 获取群组挑战列表
  async fetchGroupChallenges(groupId) {
    const token = wx.getStorageSync('token');
    try {
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/teams/${groupId}/challenge_info`,
          method: 'GET',
          header: { 'Authorization': `Bearer ${token}` },
          data: {
            lastCursor: this.data.currentGroupChallengeCursor,
            size: 10
          },
          success: resolve,
          fail: reject
        });
      });
  
      console.log('[接口完整响应]', res);
      
      if (res.statusCode === 200 && res.data.code === "0") {
        // 修改这里，正确处理返回的对象结构
        const challengeData = res.data.data;
        
        // 检查是否有有效的挑战数据
        if (!challengeData || typeof challengeData !== 'object') {
          return [];
        }
        
        // 如果接口返回的是单个挑战对象，转换为数组
        const challenges = challengeData.id ? [challengeData] : 
                         challengeData.data ? challengeData.data : 
                         [];

        console.log('[拿到的挑战数组]', challenges)
        return challenges.map(challenge => ({
          id: challenge.id || challenge.challenge_id,
          title: challenge.title || '未命名挑战',
          image: challenge.cover ? 
                `https://${apiDomain}${JSON.parse(challenge.cover).url}` : 
                '/static/images/default-challenge-cover.png',
          startTime: this.formatDate(challenge.start_time),
          endTime: this.formatDate(challenge.end_time)
        }));
      }
      
      throw new Error(res.data?.msg || '获取挑战失败');
    } catch (error) {
      console.error('获取群组挑战失败:', error);
      wx.showToast({
        title: '获取挑战失败: ' + (error.message || '未知错误'),
        icon: 'none'
      });
      return [];
    }
  },

  // 格式化日期
  formatDate(dateString) {
    if (!dateString) return '';
    const date = new Date(dateString);
    return `${date.getFullYear()}-${(date.getMonth() + 1).toString().padStart(2, '0')}-${date.getDate().toString().padStart(2, '0')}`;
  },

  // 跳转到挑战详情
  navigateToChallenge(e) {
    const challengeId = e.currentTarget.dataset.id;
    wx.navigateTo({
      url: `/pages/interaction/challenge/challenge_detail/challenge_detail?id=${challengeId}`
    });
  },
});