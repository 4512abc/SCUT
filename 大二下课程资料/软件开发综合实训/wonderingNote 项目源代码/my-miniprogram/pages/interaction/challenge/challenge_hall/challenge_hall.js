const { apiDomain } = require("../../../../config");

Page({
  data: {
    challenges: [],
    searchValue: "",
    pageSize: 10,
    hasMore: true,
    isLoading: false,
    isRefreshing: false,
    lastCursor: "0",
    showEmpty: false,
    
    // 新增搜索相关数据
    searchKeyword: "",
    isSearching: false,
    startTime: "",
    endTime: "",
    showTimePicker: false,
    selectingStartTime: true,
    minDate: new Date(2020, 0, 1).getTime(),
    maxDate: new Date().getTime(),
    currentDate: new Date().getTime(),
    formatter: (type, value) => {
      if (type === 'year') return `${value}年`;
      if (type === 'month') return `${value}月`;
      if (type === 'day') return `${value}日`;
      return value;
    }
  },

  onLoad() {
    this.loadChallenges(true);
  },
  onShow(){
    this.loadChallenges(true)
  },
  // 统一加载方法
  async loadChallenges(refresh = false) {
    if (this.data.isLoading || (!refresh && !this.data.hasMore)) return;
    
    this.setData({ 
      isLoading: true,
      isRefreshing: refresh || this.data.isRefreshing // 保持刷新状态
    });

    try {
      const token = wx.getStorageSync('token');
      const params = {
        size: this.data.pageSize,
        lastCursor: refresh ? "0" : this.data.lastCursor,
        sort: "created_at"
      };

      // 根据搜索状态添加参数
      if (this.data.isSearching) {
        if (this.data.searchKeyword) params.title = this.data.searchKeyword;
        if (this.data.startTime) params.startTime = this.data.startTime + " 00:00:00";
        if (this.data.endTime) params.endTime = this.data.endTime + " 23:59:59";
      }

      console.log('[loadChallenges] 请求参数:', params);
      
      const apiUrl = this.data.isSearching 
        ? `https://${apiDomain}/api/hall/challenges/search` 
        : `https://${apiDomain}/api/hall/challenges`;
      
      const url = this.buildUrlWithParams(apiUrl, params);
      console.log('[loadChallenges] 请求URL:', url);

      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: url,
          method: 'GET',
          header: { 
            'Authorization': token,
            'X-Request-ID': `challenge-${Date.now()}`
          },
          success: (res) => {
            if (res.statusCode === 200) {
              resolve(res.data);
            } else {
              reject(new Error(res.data?.msg || `HTTP ${res.statusCode}`));
            }
          },
          fail: reject
        });
      });

      console.log('[loadChallenges] 响应数据:', res);

      if (res.code === "0" || res.code === "200") {
        const rawData = res.data?.data || [];
        const hasMore = rawData.length >= this.data.pageSize;
        console.log('[返回数据原始响应]', res.data)
        const formattedData = rawData.map(item => {
          let avatar = '/static/images/default-avatar.jpg'
          if(item.created_avater){
            avatar = `https://${apiDomain}${JSON.parse(item.created_avater).url}`
          }
          return{
            id: item.id,
            title: item.title,
            description: item.landmark_name || '暂无描述',
            image: this.parseCoverImage(item.cover),
            user: item.creator_account || '匿名用户',
            avatar: avatar,
            endTime: this.formatTime(item.end_time),
            participants: this.formatParticipantCount(item.participants),
            tags: this.generateTags(item),
            user_id: item.created_id
          }
        });

        this.setData({
          challenges: refresh ? formattedData : [...this.data.challenges, ...formattedData],
          lastCursor: rawData.length > 0 ? rawData[rawData.length-1].id : this.data.lastCursor,
          hasMore,
          showEmpty: refresh && formattedData.length === 0,
          isLoading: false,
          isRefreshing: false
        });
      } else {
        throw new Error(res.msg || '数据加载失败');
      }
    } catch (error) {
      console.error('[loadChallenges] 加载异常:', error);
      this.setData({ isLoading: false, isRefreshing: false });
      wx.showToast({ title: error.message || '加载失败', icon: 'none' });
    }
  },

  // 构建带查询参数的URL
  buildUrlWithParams(baseUrl, params) {
    const queryString = Object.keys(params)
      .filter(key => params[key] !== undefined && params[key] !== null && params[key] !== '')
      .map(key => `${encodeURIComponent(key)}=${encodeURIComponent(params[key])}`)
      .join('&');
    
    return queryString ? `${baseUrl}?${queryString}` : baseUrl;
  },

  // 标题搜索
  onSearch(e) {
    const keyword = e.detail.trim();
    console.log('搜索关键词:', keyword);
    
    this.setData({ 
      searchValue: keyword,
      searchKeyword: keyword,
      isSearching: keyword !== "" || this.data.startTime !== "" || this.data.endTime !== "",
      lastCursor: "0",
      hasMore: true,
      challenges: [] // 清空现有数据
    });
    
    // 防抖处理
    if (this.searchTimer) clearTimeout(this.searchTimer);
    this.searchTimer = setTimeout(() => {
      this.loadChallenges(true);
    }, 500);
  },

  // 时间搜索相关方法
  showTimePicker(e) {
    const type = e.currentTarget.dataset.type;
    this.setData({
      showTimePicker: true,
      selectingStartTime: type === 'start',
      currentDate: type === 'start' ? 
        (this.data.startTime ? new Date(this.data.startTime).getTime() : new Date().getTime()) :
        (this.data.endTime ? new Date(this.data.endTime).getTime() : new Date().getTime())
    });
  },

  onTimeConfirm(e) {
    const date = new Date(e.detail);
    const formattedDate = `${date.getFullYear()}-${(date.getMonth()+1).toString().padStart(2,'0')}-${date.getDate().toString().padStart(2,'0')}`;
    
    if (this.data.selectingStartTime) {
      // 选择开始时间后，自动设置结束时间为当前日期并立即搜索
      const now = new Date();
      const endDate = `${now.getFullYear()}-${(now.getMonth()+1).toString().padStart(2,'0')}-${now.getDate().toString().padStart(2,'0')}`;
      
      this.setData({ 
        startTime: formattedDate,
        endTime: endDate,
        showTimePicker: false,
        isSearching: true,
        lastCursor: "0",
        hasMore: true,
        challenges: [] // 清空现有数据
      });
      
      // 立即触发搜索
      this.loadChallenges(true);
    } else {
      // 选择结束时间
      if (this.data.startTime && new Date(formattedDate) < new Date(this.data.startTime)) {
        wx.showToast({ title: '结束时间不能早于开始时间', icon: 'none' });
        return;
      }
      this.setData({ 
        endTime: formattedDate,
        showTimePicker: false,
        isSearching: true,
        lastCursor: "0",
        hasMore: true,
        challenges: [] // 清空现有数据
      });
      this.loadChallenges(true);
    }
  },

  onTimeCancel() {
    this.setData({ showTimePicker: false });
  },

  clearTimeSearch() {
    this.setData({
      startTime: "",
      endTime: "",
      isSearching: this.data.searchKeyword !== "",
      lastCursor: "0",
      hasMore: true,
      challenges: [] // 清空现有数据
    });
    if (this.data.searchKeyword) {
      this.loadChallenges(true);
    }
  },

  // 清除所有搜索条件
  clearSearch() {
    this.setData({ 
      searchValue: "",
      searchKeyword: "",
      startTime: "",
      endTime: "",
      isSearching: false,
      lastCursor: "0",
      hasMore: true,
      challenges: [] // 清空现有数据
    });
    this.loadChallenges(true);
  },

  // 解析封面图
  parseCoverImage(cover) {
    try {
      if (cover != '{}') {
        const coverInfo = typeof cover === 'string' ? JSON.parse(cover) : cover;
        if(coverInfo && coverInfo.length != 0){
          return `https://${apiDomain}${coverInfo.url}`
        }
      }else{
        console.log('default')
        return '/static/images/default-challenge-cover.jpg';
      }
    } catch (e) {
      console.warn('[ChallengeHall] 解析cover失败:', cover);
      return '/assets/images/default-challenge.jpg';
    }
  },

  // 格式化参与人数
  formatParticipantCount(participants) {
    try {
      const parsed = JSON.parse(participants.replace(/^'|'$/g, ''));
      const count = Array.isArray(parsed) ? parsed.length : 0;
      return count >= 10000 ? `${(count/10000).toFixed(1)}万` : count.toString();
    } catch (e) {
      console.warn('[ChallengeHall] 解析participants失败:', participants);
      return '0';
    }
  },

  // 生成标签
  generateTags(item) {
    const tags = [];
    if (item.object_type) tags.push(item.object_type);
    if (item.gesture_type) tags.push(item.gesture_type);
    return tags.length > 0 ? tags : ['热门挑战'];
  },

  // 格式化时间
  formatTime(timeStr) {
    if (!timeStr) return '长期有效';
    try {
      const date = new Date(timeStr);
      if (isNaN(date.getTime())) return '长期有效';
      
      const now = new Date();
      const diffDays = Math.floor((date - now) / (1000 * 60 * 60 * 24));
      
      if (diffDays < 0) return '已结束';
      if (diffDays === 0) return '今天截止';
      if (diffDays < 7) return `${diffDays}天后截止`;
      
      return `${date.getMonth() + 1}月${date.getDate()}日截止`;
    } catch (e) {
      console.warn('[ChallengeHall] 格式化时间异常:', timeStr);
      return '长期有效';
    }
  },

  // 跳转到详情页
  navigateToDetail(e) {
    const index = e.currentTarget.dataset.index;
    const challenge = this.data.challenges[index];
    if (!challenge) {
      console.error('未获取到挑战数据:', this.data.challenges);
      return;
    }
    
    const challengeId = challenge.id;
    if (!challengeId) {
      console.error('[ChallengeHall] 无效的挑战ID');
      return wx.showToast({ title: '数据异常', icon: 'none' });
    }
    
    wx.navigateTo({
      url: `/pages/interaction/challenge/challenge_detail/challenge_detail?id=${challengeId}`,
      fail: (err) => {
        console.error('跳转失败', err);
        wx.showToast({ title: '跳转失败，请重试', icon: 'none' });
      }
    });
  },

  // 下拉刷新
  onPullDownRefresh() {
    console.log('[onPullDownRefresh] 触发下拉刷新');
    
    // 显示导航栏加载动画
    wx.showNavigationBarLoading();
    
    // 重置分页参数
    this.setData({
      lastCursor: "0",
      hasMore: true,
      challenges: [],  // 清空当前数据
      isRefreshing: true  // 设置刷新状态
    });
    
    // 调用原有loadChallenges方法
    this.loadChallenges(true).finally(() => {
      // 无论成功失败都停止动画
      wx.stopPullDownRefresh();
      wx.hideNavigationBarLoading();
      this.setData({ isRefreshing: false });
      console.log('[onPullDownRefresh] 刷新完成');
    });
  },

  // 上拉加载更多
  onReachBottom() {
    if (!this.data.isLoading && this.data.hasMore) {
      this.loadChallenges();
    }
  },

  // 跳转到创建挑战页面
  navigateToCreate() {
    wx.navigateTo({
      url: '/pages/interaction/challenge/create_challenge/create_challenge',
    })
  },
  navigateToUserDetail(e){
    const userId = e.currentTarget.dataset.userid;
    console.log('[DEBUG] 点击了头像，用户ID:', userId);

    // 示例：跳转用户详情页
    wx.navigateTo({
      url: `/pages/interaction/user_profile/user_profile?id=${userId}`
    });
  },
  onHide(){
    this.setData({
      searchKeyword : '',
      searchValue: ''
    })
  }
});