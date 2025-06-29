const { apiDomain } = require("../../../config");

// pages/my/my.js
Page({
  data: {
    userInfo: {
      nickname: '请先编辑资料',
      avatar: '/static/images/default-avatar.jpg',
      noteCount: 0,
      location: '在下方设置中完成编辑',
      status: '',
      createTime: ''
    },
    loading: false
  },
  
  onLoad() {
    this.fetchUserInfo();
    this.setTheme(wx.getStorageSync('theme') || 0);
  },

  onShow() {
    this.fetchUserInfo();
  },

  async fetchUserInfo() {
    if (this.data.loading) return;
    this.setData({ loading: true });

    try {
      const token = wx.getStorageSync('token');
      if (!token) {
        throw new Error('请先登录');
      }

      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/auth/home_info`, // 替换为实际API地址
          method: 'GET',
          header: {
            'content-type': 'application/json',
            'Authorization': `Bearer ${token}`
          },
          success: (res) => {
            if (res.statusCode === 200) {
              resolve(res.data);
            } else {
              reject(new Error(res.data.msg || '请求失败'));
            }
          },
          fail: (err) => {
            reject(new Error('网络错误，请稍后重试'));
          }
        });
      });

      if (res.code === '0') {
        console.log(res)
        const { base_info,  profile_info} = res.data;
        
        let avatar = '/static/images/default-avatar.jpg'
        if (base_info.avatar){
          avatar = `https://${apiDomain}${JSON.parse(base_info.avatar).url}`
        }
        console.log(base_info.avatar)
        console.log(avatar)
        if(profile_info != null){
          this.setData({
            userInfo: {
              nickname: base_info.account || '未设置昵称',
              avatar: avatar,
              noteCount: 0, // 根据实际接口返回修改
              status: base_info.status,
              createTime: base_info.create_time,
              location: profile_info.location
            }
          });
          console.log(this.data.avatar)
          // 存储到全局
          getApp().globalData.userInfo = {
            ...base_info,
            ...profile_info
          };
          console.log('[DEBUG] 全局数据已更新:', getApp().globalData.userInfo);
        }
        // 如果有未读消息，显示小红点
        if (res.data.unreadMessageCount > 0) {
          wx.showTabBarRedDot({
            index: 4 // 个人中心的 tabBar 索引
          });
        } else {
          wx.hideTabBarRedDot({
            index: 4
          });
        }
      } else {
        throw new Error(res.msg);
      }
    } catch (error) {
      console.error('获取用户信息失败:', error);
      wx.showToast({
        title: error.message || '获取信息失败',
        icon: 'none'
      });
    } finally {
      this.setData({ loading: false });
    }
  },

  onPullDownRefresh() {
    this.fetchUserInfo().finally(() => {
      wx.stopPullDownRefresh();
    });
  },

  setTheme(themeIndex) {
    // 主题设置逻辑
    wx.setStorageSync('theme', themeIndex);
  }
});