const { apiDomain } = require("../../../config")

import Toast from '@vant/weapp/toast/toast'
Page({
  data: {
    avatarUrl: '',
    nickname: '',
    bio: '',
    gender: null,
    birthday: '',
    location: '',
    currentDate: new Date().toISOString().split('T')[0],
    loading: false,
    region: [],
    location: '',
    faceRegistered: false, // 是否已注册人脸
    isNicknameChanged: false,  // 标记用户名是否被修改
    originalNickname: ''       // 保存原始用户名
  },

  async onLoad() {
    console.log('[DEBUG] 页面开始加载');
    try {
      await this.fetchUserProfile();
      await this.checkFaceRegistration(); 
      this.setData({
        originalNickname: this.data.nickname
      });
      
      const savedTheme = wx.getStorageSync('theme') || 0;
      this.setTheme(savedTheme);
    } catch (error) {
      console.error('[DEBUG] 页面加载过程中出错:', error);
    }
    console.log('[DEBUG] 页面加载完成');
  },

  // 获取用户资料
  async fetchUserProfile() {
    const token = wx.getStorageSync('token');
    this.setData({ loading: true });
    try {
      
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/auth/home_info`,
          method: 'GET',
          header: {
            'Authorization': `Bearer ${token}`
          },
          success: (res) => {
            console.log('[DEBUG] 请求成功，响应数据:', res.data);
            resolve(res);
          },
          fail: (err) => {
            console.error('[DEBUG] 请求失败:', err);
            reject(err);
          }
        });
      });
  
      console.log('[DEBUG] 完整响应:', res);
  
      if (res.data.code === '200' || res.data.code === '0') {
        if (res.data.data.profile_info != null){
          const { base_info, profile_info } = res.data.data;
          // 处理头像数据
          let avatarUrl = '/images/default-avatar.jpg';
          try {
            const avatarData = base_info.avatar ? JSON.parse(base_info.avatar) : null;
            avatarUrl = `https://${apiDomain}${avatarData.url}`
          } catch (e) {
            console.error('[DEBUG] 头像解析失败:', e);
          }
    
          // 处理地区信息
          const location = profile_info?.location || '';
          const region = location ? location.split(' ') : ['', '', ''];
        
          const updateData = {
            avatarUrl,
            nickname: base_info.account || '',
            originalNickname: base_info.account || '',
            bio: profile_info?.bio || '',
            gender: profile_info?.gender || null,
            birthday: this.formatDate(profile_info.birthday) || '',
            location,
            region,
            userBaseInfo: base_info,
            userProfileInfo: profile_info || {}
          };
    
          this.setData(updateData);
          console.log('[DEBUG] 数据更新完成，当前data状态:', this.data);
    
          // 存储到全局
          getApp().globalData.userInfo = {
            ...base_info,
            ...profile_info
          };
          console.log('[DEBUG] 全局数据已更新:', getApp().globalData.userInfo);
        }
        else{
          const { base_info, profile_info } = res.data.data;
          // 处理头像数据
          let avatarUrl = '/images/default-avatar.jpg';
    
          // 处理地区信息
          const location = '';
          const region = '未知地点'
        
          const updateData = {
            avatarUrl,
            nickname: base_info.account || '',
            originalNickname: base_info.account || '',
            bio: '',
            gender: null,
            birthday: null,
            location,
            region,
            userBaseInfo: base_info,
            userProfileInfo: profile_info || {}
          };
    
          this.setData(updateData);
          console.log('[DEBUG] 数据更新完成，当前data状态:', this.data);
    
          // 存储到全局
          getApp().globalData.userInfo = {
            ...base_info,
            ...profile_info
          };
          console.log('[DEBUG] 全局数据已更新:', getApp().globalData.userInfo);
        }
      } else {
        console.error('[DEBUG] 接口返回异常:', res.data.msg || '未知错误');
      }
    } catch (error) {
      console.error('[DEBUG] 获取用户信息失败:', error);
  /**
   * 显示操作菜单并处理用户选择拍照或从相册选择图片
   * 
   * 当用户点击后会弹出底部菜单，提供两个选项：
   * 1. 拍摄照片
   * 2. 从相册选择
   * 
   * 根据用户的选择分别调用 takePhoto 或 chooseFromAlbum 方法
   * 
   * @async
   * @function chooseImage
   * @returns {Promise<void>}
   */
      wx.showToast({
        title: '获取资料失败',
        icon: 'none'
      });
    } finally {
      this.setData({ loading: false });
      console.log('[DEBUG] 请求流程结束');
    }
  },

  // 选择图片
  async chooseImage() {
    wx.showActionSheet({
      itemList: ['拍摄照片', '从相册选择'],
      success: (res) => {
        if (res.tapIndex === 0) {
          this.takePhoto()
        } else {
          this.chooseFromAlbum()
        }
      }
    })
  },

  // 拍照
  async takePhoto() {
    try {
      const res = await wx.chooseMedia({
        count: 1,
        mediaType: ['image'],
        sourceType: ['camera']
      })
      await this.uploadImage(res.tempFiles[0].tempFilePath)
    } catch (error) {
      console.error('拍照失败:', error)
    }
  },

  // 从相册选择
  async chooseFromAlbum() {
    try {
      const res = await wx.chooseMedia({
        count: 1,
        mediaType: ['image'],
        sourceType: ['album']
      })
      await this.uploadImage(res.tempFiles[0].tempFilePath)
    } catch (error) {
      console.error('选择图片失败:', error)
    }
  },

  // 上传头像
  async uploadImage(filePath) {
    const token = wx.getStorageSync('token')
    wx.showLoading({ title: '上传中...' })

    try {
      const uploadRes = await new Promise((resolve, reject) => {
        wx.uploadFile({
          url: `https://${apiDomain}/api/auth/avatar_update`,
          filePath: filePath,
          name: 'file',
          header: {
            'Authorization': `Bearer ${token}`,
            'Content-Type': 'multipart/form-data'
          },
          success: resolve,
          fail: reject
        })
      })
      console.log('[上传接口响应]', uploadRes)

      const resData = JSON.parse(uploadRes.data)
      console.log('[上传接口数据]', resData)
      console.log('[接口返回码]', resData.code)
      if (resData.code === '200' || resData.code === '0') {
        console.log('[转换后的url]',`https://${apiDomain}:8888${JSON.parse(resData.data.file_url).url}`)
        this.setData({ 
          avatarUrl: `https://${apiDomain}${JSON.parse(resData.data.file_url).url}` 
        })
        
        wx.showToast({
          title: '头像上传成功',
          icon: 'success'
        })
        console.log("成功！")
      }
    } catch (error) {
      Toast.fail("头像更新失败")
      console.log("失败！")
    } finally {
      wx.hideLoading()
    }
  },

  // 表单字段变更处理
  onNicknameChange(e) {
    const newNickname = e.detail.value
    this.setData({
      nickname: newNickname,
      isNicknameChanged: newNickname !== this.data.originalNickname
    })
  },

  onBioChange(e) {
    this.setData({ bio: e.detail.value })
  },

  selectGender(e) {
    this.setData({ gender: e.currentTarget.dataset.gender })
  },

  onDateChange(e) {
    this.setData({ birthday: e.detail.value})
  },

  onRegionChange(e) {
    const value = e.detail.value;
    this.setData({
      region: value,
      location: value.join(' ')
    }, () => {
      // 回调确认数据已更新
      console.log('当前数据:', this.data.region, this.data.location); 
    });
  },
  

  // 表单验证
  validateForm() {
    if (!this.data.nickname.trim()) {
      wx.showToast({
        title: '请输入用户名',
        icon: 'none'
      })
      return false
    }
    if (!this.data.bio.trim()) {
      wx.showToast({
        title: '请输入简介',
        icon: 'none'
      })
      return false
    }
    if (this.data.gender == null) {
      wx.showToast({
        title: '请选择性别',
        icon: 'none'
      })
      return false
    }
    if (this.data.birthday == null) {
      wx.showToast({
        title: '请选择出生日期',
        icon: 'none'
      })
      return false
    }
    if (this.data.region == null || this.data.region == '未知') {
      wx.showToast({
        title: '请选择所在地区',
        icon: 'none'
      })
      return false
    }
    return true
  },

  // 保存资料
  async saveProfile() {
    if (!this.validateForm()) return;
  
    const token = wx.getStorageSync('token');
    this.setData({ loading: true });
  
    try {
      // 1. 如果需要修改用户名
      if (this.data.isNicknameChanged) {
        await this.resetAccount(this.data.nickname);
        // 更新原始用户名记录
        this.setData({ originalNickname: this.data.nickname });
      }
  
      // 2. 更新其他资料
      const updateRes = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/auth/update`,
          method: 'PUT',
          header: {
            'Authorization': `Bearer ${token}`,
            'Content-Type': 'application/json'
          },
          data: {
            gender: this.data.gender,
            birthday: this.data.birthday + " 00:00:00",
            bio: this.data.bio,
            location: this.data.location,
            settings: JSON.stringify({
              nickname: this.data.nickname
            })
            
          },
          success: resolve,
          fail: reject
        });
      });
  
      if (updateRes.data.code !== '0') {
        throw new Error(updateRes.data.msg || '资料保存失败');
      }
  
      // 3. 重新获取最新资料
      await this.fetchUserProfile();
  
      wx.showToast({
        title: '资料保存成功',
        icon: 'success',
        duration: 1500,
        success: () => {
          setTimeout(() => wx.navigateBack(), 1500);
        }
      });
    } catch (error) {
      console.error('保存失败:', error);
      wx.showToast({
        title: error.message || '保存失败',
        icon: 'none'
      });
    } finally {
      this.setData({ loading: false });
    }
  },
  
  // 单独封装的resetAccount方法
  async resetAccount(newAccount) {
    const token = wx.getStorageSync('token')
    const res = await new Promise((resolve, reject) => {
      wx.request({
        url: `https://${apiDomain}/api/auth/reset_account`,
        method: 'POST',
        header: {
          'Authorization': `Bearer ${token}`,
          'Content-Type': 'application/json'
        },
        data: { account: newAccount },
        success: (res) => resolve(res.data),
        fail: reject
      })
    })
    return res
  },
  
  // 单独封装的updateProfile方法
  async updateProfile() {
    const token = wx.getStorageSync('token')
    const res = await new Promise((resolve, reject) => {
      wx.request({
        url: `https://${apiDomain}/api/auth/update`,
        method: 'PUT',
        header: {
          'Authorization': `Bearer ${token}`,
          'Content-Type': 'application/json'
        },
        data: {
          gender: this.data.gender,
          birthday: this.data.birthday,
          bio: this.data.bio,
          location: this.data.location,
          settings: JSON.stringify({
            nickname: this.data.nickname
          })
        },
        success: (res) => resolve(res.data),
        fail: reject
      })
    })
    return res
  },
    // 格式化日期显示
  formatDate(dateString) {
    if (!dateString) return '';
    const date = new Date(dateString);
    return `${date.getFullYear()}-${(date.getMonth()+1).toString().padStart(2,'0')}-${date.getDate().toString().padStart(2,'0')}`;
  },

  // 获取用户状态文本
  getStatusText(status) {
    const statusMap = {
      'ACTIVE': '正常',
      'FROZEN': '已冻结',
      'DELETE': '已删除',
      'SUSPENDED': '已暂停'
    };
    return statusMap[status] || '未知状态';
  },
  navigateBack() {
    wx.navigateBack()
  },

  // 注册人脸向量
  async registerFace() {
    wx.showModal({
      title: '提示',
      content: '一个账号只能注册一次人脸，请选取正对屏幕的清晰照片。是否继续？',
      success: async (res) => {
        if (res.confirm) {
          try {
            const chooseRes = await wx.chooseMedia({
              count: 1,
              mediaType: ['image'],
              sourceType: ['album', 'camera']
            });
  
            const token = wx.getStorageSync('token');
            wx.showLoading({ title: '注册中...' });
  
            await new Promise((resolve, reject) => {
              wx.uploadFile({
                url: `https://${apiDomain}/flask/api/face/register`,
                filePath: chooseRes.tempFiles[0].tempFilePath,
                name: 'image',
                header: {
                  'Authorization': `Bearer ${token}`,
                  'Content-Type': 'multipart/form-data'
                },
                success: (res) => {
                  console.log(res)
                  const data = JSON.parse(res.data)
                  console.log(typeof(data))
                  console.log(data.code)
                  if (data.code === 0 ) {
                    wx.showToast({ title: '注册成功', icon: 'success' });
                    this.setData({ faceRegistered: true });
                    resolve();
                  } else {
                    throw new Error(data.msg || '注册失败');
                  }
                },
                fail: reject
              });
            });
  
          } catch (err) {
            console.error('注册失败:', err);
            wx.showToast({ title: '注册失败', icon: 'none' });
          } finally {
            wx.hideLoading();
          }
        }
      }
    });
  },
  
  
  async checkFaceRegistration() {
    const token = wx.getStorageSync('token');
    try {
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
      if (res.code === 0 || res.code === '200') {
        this.setData({ faceRegistered: true });
      }else if(res.code === -1) {
        this.setData({ faceRegistered: false });
      }else{
        console.warn('人脸检测返回异常:', res);
      }
      console.log(this.data.faceRegistered)
    } catch (err) {
      console.error('检测人脸注册状态失败:', err);
    }
  },
  

  setTheme(themeIndex) {
    // 主题设置逻辑
  }
})