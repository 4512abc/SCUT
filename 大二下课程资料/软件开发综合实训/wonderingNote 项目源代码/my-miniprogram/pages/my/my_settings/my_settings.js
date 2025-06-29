const { apiDomain } = require("../../../config")

Page({
  data: {
    showThemePicker: false,
    notificationEnabled: true,
    selectedTheme: 0,
    version: '1.2.0',
    loading: false,
    themes: [
      { 
        name: '经典白',
        color: '#ffffff',
        navColor: '#ffffff',
        textColor: '#333333',
        themeVars: {
          'nav-bar-background-color': '#ffffff',
          'nav-bar-title-text-color': '#333333',
          'cell-background-color': '#ffffff',
          'text-color': '#333333',
          'background-color': '#ffffff'
        }
      },
      {
        name: '薄荷绿',
        color: '#e6f9f2',
        navColor: '#d0f0e0',
        textColor: '#2e6d5c',
        themeVars: {
          'nav-bar-background-color': '#d0f0e0',
          'nav-bar-title-text-color': '#2e6d5c',
          'cell-background-color': '#e6f9f2',
          'text-color': '#2e6d5c',
          'background-color': '#e6f9f2'
        }
      },
      {
        name: '雾霾蓝',
        color: '#e8f0f9',
        navColor: '#d3e4f0',
        textColor: '#2c4a60',
        themeVars: {
          'nav-bar-background-color': '#d3e4f0',
          'nav-bar-title-text-color': '#2c4a60',
          'cell-background-color': '#e8f0f9',
          'text-color': '#2c4a60',
          'background-color': '#e8f0f9'
        }
      },
      {
        name: '樱花粉',
        color: '#fff0f5',
        navColor: '#ffe4ec',
        textColor: '#80324e',
        themeVars: {
          'nav-bar-background-color': '#ffe4ec',
          'nav-bar-title-text-color': '#80324e',
          'cell-background-color': '#fff0f5',
          'text-color': '#80324e',
          'background-color': '#fff0f5'
        }
      },
      {
        name: '浅杏黄',
        color: '#fff9e6',
        navColor: '#fff2cc',
        textColor: '#6b5b3e',
        themeVars: {
          'nav-bar-background-color': '#fff2cc',
          'nav-bar-title-text-color': '#6b5b3e',
          'cell-background-color': '#fff9e6',
          'text-color': '#6b5b3e',
          'background-color': '#fff9e6'
        }
      },
      {
        name: '天空蓝',
        color: '#eaf8ff',
        navColor: '#d0ecff',
        textColor: '#2d5c88',
        themeVars: {
          'nav-bar-background-color': '#d0ecff',
          'nav-bar-title-text-color': '#2d5c88',
          'cell-background-color': '#eaf8ff',
          'text-color': '#2d5c88',
          'background-color': '#eaf8ff'
        }
      }
    ]    
  },

  async onLoad() {
    // await this.fetchUserSettings()
  },

  // async fetchUserSettings() {
  //   if (this.data.loading) return
  //   this.setData({ loading: true })

  //   try {
  //     const token = wx.getStorageSync('token')
  //     const res = await request({
  //       url: `http://${apiDomain}:8888/api/user/settings`,
  //       method: 'GET',
  //       header: {
  //         'Authorization': token
  //       }
  //     })

  //     if (res.data.code === '0') {
  //       const { notificationEnabled, theme } = res.data.data
  //       this.setData({ notificationEnabled })
  //       this.setTheme(theme || 0)
  //     } else {
  //       throw new Error(res.data.msg)
  //     }
  //   } catch (error) {
  //     wx.showToast({
  //       title: error.message || '获取设置失败',
  //       icon: 'none'
  //     })
  //   } finally {
  //     this.setData({ loading: false })
  //   }
  // },

  // async updateSettings(settings) {
  //   try {
  //     const token = wx.getStorageSync('token')
  //     const res = await request({
  //       url: `http://${apiDomain}:8888/api/user/update`,
  //       method: 'POST',
  //       header: {
  //         'Authorization': token
  //       },
  //       data: settings
  //     })

  //     if (res.data.code !== '0') {
  //       throw new Error(res.data.msg)
  //     }
  //   } catch (error) {
  //     wx.showToast({
  //       title: error.message || '更新设置失败',
  //       icon: 'none'
  //     })
  //   }
  // },

  async onNotificationChange(event) {
    const notificationEnabled = event.detail
    this.setData({ notificationEnabled })
    await this.updateSettings({ notificationEnabled })
    wx.setStorageSync('notification', notificationEnabled)
  },

  showThemePicker() {
    this.setData({ showThemePicker: true })
  },

  closeThemePicker() {
    this.setData({ showThemePicker: false })
  },

  async onThemeSelect(event) {
    const index = event.currentTarget.dataset.index
    await this.updateSettings({ theme: index })
    this.setTheme(index)
    this.closeThemePicker()
  },

  setTheme(index) {
    if (index < 0 || index >= this.data.themes.length) return

    const theme = this.data.themes[index]
    const isDark = this.calculateLuminance(theme.navColor) < 0.5

    const newThemeVars = {
      'nav-bar-background-color': theme.navColor,
      'nav-bar-title-text-color': isDark ? '#ffffff' : '#333333',
      'nav-bar-arrow-color': isDark ? '#ffffff' : '#333333',
      'cell-background-color': theme.color
    }

    wx.setNavigationBarColor({
      frontColor: isDark ? '#ffffff' : '#000000',
      backgroundColor: theme.navColor,
      animation: { duration: 300 }
    })

    wx.setBackgroundColor({
      backgroundColor: theme.color,
      success: () => {
        this.setData({
          selectedTheme: index,
          themeVars: newThemeVars
        })
        wx.setStorageSync('theme', index)
      }
    })
  },

  calculateLuminance(hexColor) {
    const hex = hexColor.replace('#', '')
    const r = parseInt(hex.substring(0,2), 16) / 255
    const g = parseInt(hex.substring(2,4), 16) / 255
    const b = parseInt(hex.substring(4,6), 16) / 255
    return 0.2126 * r + 0.7152 * g + 0.0722 * b
  },

  onHelpCenter() {
    wx.showToast({ title: '功能开发中...', icon: 'none' })
  },

  showAbout() {
    wx.showModal({
      title: '关于我们',
      content: '游记分享平台 v1.2.0\n\n开发团队：旅行科技组\n核心功能：\n- 旅行记录\n- 地点分享\n- 智能推荐',
      showCancel: false
    })
  },

  onBack() {
    wx.navigateBack()
  }
})