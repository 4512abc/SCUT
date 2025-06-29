const { apiDomain } = require("../../../../config");

Page({
  data: {
    groupTitle: '',
    groupDesc: '',
    maxMembers: '50', // 默认值设为50
    logoUrl: '',
    isPrivate: true,
    submitting: false,
    members: [
      { name: "昵称", checked: true, required: true, field: "nickname" },
      { name: "头像", checked: true, required: true, field: "avatar" },
      { name: "爱好", checked: false, field: "hobby" },
      { name: "人像", checked: false, field: "face" },
      { name: "手机号", checked: false, field: "phone" }
    ],
    displayUrl: ''
  },

  onLoad() {
    // 初始化主题等设置
    const savedTheme = wx.getStorageSync('theme') || 0;
    this.setTheme(savedTheme);
  },

  // 上传群组LOGO
async uploadLogo() {
  try {
    // 1. 选择图片
    const { tempFilePaths } = await wx.chooseImage({
      count: 1,
      sizeType: ['compressed'],
      sourceType: ['album', 'camera']
    });
    
    if (!tempFilePaths || tempFilePaths.length === 0) {
      throw new Error('未选择图片');
    }

    wx.showLoading({ 
      title: '上传中...',
      mask: true
    });

    // 2. 上传到服务器
    const uploadRes = await new Promise((resolve, reject) => {
      wx.uploadFile({
        url: `https://${apiDomain}/api/files/upload`,
        filePath: tempFilePaths[0],
        name: 'file',
        header: { 
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'multipart/form-data'
        },
        success: resolve,
        fail: reject
      });
    });

    // 3. 解析响应数据（兼容多种格式）
    let responseData;
    try {
      // 尝试解析JSON，兼容字符串和对象格式
      responseData = typeof uploadRes.data === 'string' 
        ? JSON.parse(uploadRes.data) 
        : uploadRes.data;
      
      console.log('上传响应数据:', responseData); // 调试日志
      
      // 兼容不同后端响应结构
      const fileUrl = responseData.data.file_url

      console.log(fileUrl)
      const displayUrlJson = typeof fileUrl === 'string' 
        ? JSON.parse(fileUrl) 
        : fileUrl;
      this.setData({displayUrl: `https://${apiDomain}${displayUrlJson.url}`})
      console.log(this.data.displayUrl)

      
      // 4. 更新UI
      this.setData({ 
        logoUrl: fileUrl,
        uploadStatus: {
          ...this.data.uploadStatus,
          logo: {
            status: 'success',
            message: '上传成功',
            fileInfo: responseData.data || responseData
          }
        }
      });

      wx.showToast({
        title: 'LOGO上传成功',
        icon: 'success',
        duration: 2000
      });
      console.log(fileUrl)
      return fileUrl; // 返回文件URL供后续使用

    } catch (e) {
      console.error('解析响应数据失败:', e);
      throw new Error(`解析服务器响应失败: ${e.message}`);
    }

  } catch (error) {
    console.error('[上传错误]', error);
    
    this.setData({
      uploadStatus: {
        ...this.data.uploadStatus,
        logo: {
          status: 'error',
          message: error.message.replace('解析服务器响应失败: ', ''),
          rawError: error
        }
      }
    });

    let toastMsg = '上传失败';
    if (error.message.includes('未选择图片')) {
      toastMsg = '请先选择图片';
    } else if (error.message.includes('服务器返回')) {
      toastMsg = '服务器返回数据异常';
    }

    wx.showToast({ 
      title: toastMsg,
      icon: 'none',
      duration: 3000
    });

    // 抛出错误供外部捕获
    throw error;

  } finally {
    wx.hideLoading();
  }
},

  // 输入处理函数
  onTitleInput(e) {
    this.setData({ groupTitle: e.detail });
  },

  onMaxMembersInput(e) {
    const value = e.detail;
    // 确保输入的是正整数
    if (/^\d*$/.test(value)) {
      this.setData({ maxMembers: value });
    }
  },

  onDescInput(e) {
    this.setData({ groupDesc: e.detail });
  },

  // 切换信息收集项
  toggleCheck(e) {
    const index = e.currentTarget.dataset.index;
    const members = [...this.data.members];
    
    if (!members[index].required) {
      members[index].checked = !members[index].checked;
      this.setData({ members });
    }
  },

  // 添加更多信息项
  addMoreInfo() {
    const additionalFields = [
      { name: '位置', field: 'location' },
      { name: '联系方式', field: 'contact' },
      { name: '备注', field: 'remark' }
    ];

    wx.showActionSheet({
      itemList: additionalFields.map(item => `添加${item.name}`),
      success: (res) => {
        const newField = additionalFields[res.tapIndex];
        const members = [...this.data.members];
        
        if (!members.find(m => m.field === newField.field)) {
          members.push({
            name: newField.name,
            field: newField.field,
            checked: false,
            required: false
          });
          this.setData({ members });
        } else {
          wx.showToast({
            title: '该信息项已存在',
            icon: 'none'
          });
        }
      }
    });
  },

  // 表单验证
  validateForm() {
    if (!this.data.groupTitle.trim()) {
      wx.showToast({
        title: '请输入群组标题',
        icon: 'none'
      });
      return false;
    }

    if (!this.data.logoUrl) {
      wx.showToast({
        title: '请上传群组LOGO',
        icon: 'none'
      });
      return false;
    }

    if (!this.data.maxMembers || isNaN(parseInt(this.data.maxMembers)) || parseInt(this.data.maxMembers) <= 0) {
      wx.showToast({
        title: '请输入有效的最大成员数',
        icon: 'none'
      });
      return false;
    }

    return true;
  },

  // 创建群组
  async createGroup() {
    if (!this.validateForm() || this.data.submitting) return;

    this.setData({ submitting: true });

    try {
      const token = wx.getStorageSync('token');
      console.log({
        name: this.data.groupTitle,
            logo: this.data.logoUrl,
            max_members: parseInt(this.data.maxMembers)
      })
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/teams/create`,
          method: 'POST',
          header: {
            'Authorization': `Bearer ${token}`,
            'Content-Type': 'application/json'
          },
          data: {
            name: this.data.groupTitle,
            logo: this.data.logoUrl,
            max_members: parseInt(this.data.maxMembers)
            // 其他可选字段可以根据需要添加
          },
          success: resolve,
          fail: reject
        });
      });

      if (res.data.code === '200' || res.data.code === '0') {
        wx.showToast({
          title: '创建成功',
          icon: 'success',
          duration: 1500
        });
        
        // 返回上一页
        setTimeout(() => {
          wx.navigateBack();
        }, 1500);
      } else {
        throw new Error(res.data.msg || '创建失败');
      }
    } catch (error) {
      console.error('创建群组失败:', error);
      wx.showToast({
        title: error.message || '创建失败',
        icon: 'none'
      });
    } finally {
      this.setData({ submitting: false });
    }
  },

  // 返回上一页
  navigateBack() {
    wx.navigateBack();
  },

  // 设置主题（示例方法）
  setTheme(themeIndex) {
    // 这里可以实现主题切换逻辑
    console.log('设置主题:', themeIndex);
  }
});