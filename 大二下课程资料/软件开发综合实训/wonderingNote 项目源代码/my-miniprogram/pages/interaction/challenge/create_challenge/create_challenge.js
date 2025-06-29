const { apiDomain } = require("../../../../config")

Page({
  data: {
    currentTime: '',
    markers: [],
    showObjectModeDialog: false,
    formData: {
      title: '',
      gestureType: 'heart',
      landmark_name: '',
      description: '',
      object_type: '',
      radius: null,
      location: {
        lng: 113.324520,
        lat: 23.099994
      },
      checkMode: 'none',
      needFaceVerify: 0,
      team_id: null,
      startTime: '',   // 存储ISO格式
      endTime: '',      // 存储ISO格式
      groups: [],
      gesture_type: '不设置',
      images: []
    },
    descriptionLength: 0,
    tempImages: [], // 临时存储选择的图片路径
    uploading: false, // 上传状态
    rangeOptions: [
      { label: '请选择范围', value: null },
      { label: '50米', value: 50 },
      { label: '200米', value: 200 },
      { label: '500米', value: 500 },
      { label: '1公里', value: 1000 },
      { label: '自定义', value: 'custom' }
    ],
    selectedRangeIndex: 0, // 初始选择"请选择范围"
    showCustomRangeInput: false,
    customRangeValue: '',
    showRangeInputDialog: false, // 新增：控制自定义范围输入弹窗
    tempCustomRange: '', // 临时存储自定义范围值
    rangeDisplayText: '请选择范围', // 新增：用于显示的范围文本

    gestureOptions: [
      { value: '不设置', name: '不设置' },
      { value: '握拳', name: '👊 握拳' },
      { value: '张开手掌', name: '🖐️ 张开手掌' },
      { value: '手指向上', name: '👆 手指向上' },
      { value: '点赞', name: '👍 点赞' }, 
      { value: '胜利手势', name: '✌️ 胜利手势' },
      { value: '我爱你手势', name: '🤟 我爱你手势' }
    ],
    // 特殊打卡选项
    specialCheckOptions: [
      { value: 'scene', label: '场景识别' },
      { value: 'object', label: '物体识别' }
    ],
    // 场景选项（保持不变）
    sceneOptions: [
      { value: '无', label: '无' },
      { value: '海洋', label: '🌊 海洋' },
      { value: '森林', label: '🌲 森林' },
      { value: '山脉', label: '⛰️ 山脉' },
      { value: '街道', label: '🛣️ 街道' },
      { value: '建筑', label: '🏘️ 建筑' }
    ],
    currentSceneLabel: '',
    tempObjectImage: '',
    objectDetectResult: '',
    selectedGestureIndex: 0, // 记录当前选中的索引
    showGesturePicker: false, // 新增：控制选择器显示
    currentGestureLabel: '无', // 新增：当前显示的手势标签

    selectedGroup: null, // 当前选中的群组（单选）
    showGroupPicker: false,
    availableGroups: [],
    loadingGroups: false,
    groupNextCursor: 0,
    hasMoreGroups: true,
    
    showStartPicker: false,
    showEndPicker: false,
    minDate: new Date().getTime(), // 当前时间作为最小日期
    maxDate: new Date(new Date().setMonth(new Date().getMonth() + 3)).getTime(), // 当前时间+3个月
    currentStartDate: new Date().getTime(),
    currentEndDate: new Date().getTime(),
    startDateTime: '', // 格式：'2023-03-14 12:30:45'
    endDateTime: '',
    
    submitting: false,
    formValid: false,
    locationSelected: false,
    
    validationErrors: [],
    validationErrorText: '', // 用于显示的拼接字符串
    formatter: (type, value) => {
      if (type === 'year') {
        return `${value}年`;
      }
      if (type === 'month') {
        return `${value}月`;
      }
      if (type === 'day') {
        return `${value}日`;
      }
      if (type === 'hour') {
        return `${value}时`;
      }
      if (type === 'minute') {
        return `${value}分`;
      }
      return value;
    },
  },

  onLoad() {
    this.initMap()
    this.initTimeArray()
    this.updateCurrentTime()
    this.checkFormValid()
    this.updateCurrentGestureLabel();
    const savedTheme = wx.getStorageSync('theme') || 0;
    this.setTheme(savedTheme);

    console.log('时间选择器初始化完成', {
      start: this.data.startDateTime,
      end: this.data.endDateTime
    });
  },

  // 初始化地图
  initMap() {
    this.mapCtx = wx.createMapContext('map')
    wx.getLocation({
      type: 'gcj02',
      success: res => {
        const { longitude, latitude } = res
        this.setData({
          'formData.location.lng': longitude,
          'formData.location.lat': latitude,
          markers: [{
            id: 1,
            longitude,
            latitude,
            iconPath: '/images/marker.jpg',
            width: 30,
            height: 30
          }]
        })
      },
      fail: err => {
        console.error('获取位置失败:', err)
        wx.showToast({
          title: '获取位置失败',
          icon: 'none'
        })
      }
    })
  },

  // 更新当前时间
  updateCurrentTime() {
    const now = new Date()
    const hours = now.getHours().toString().padStart(2, '0')
    const minutes = now.getMinutes().toString().padStart(2, '0')
    this.setData({ currentTime: `${hours}:${minutes}` })
  },

  // 标题输入
  onTitleInput(e) {
    this.setData({
      title: e.detail.value
    })
    this.checkFormValid()
  },

  // 显示手势选择器
  showGesturePicker() {
    console.log('[调试] 打开手势选择器');
    this.setData({ showGesturePicker: true });
  },

  // 手势选择处理（修改后）
  handleGestureSelect(event) {
    console.log('[调试] 选择事件:', event);
    const selected = event.detail;
    this.setData({
      'formData.gesture_type': selected.value, // 直接使用中文值
      currentGestureLabel: selected.name,
      showGesturePicker: false
    });
    this.checkFormValid();
  },

    // 隐藏手势选择器
  hideGesturePicker() {
    console.log('[调试] 关闭手势选择器');
    this.setData({ showGesturePicker: false });
  },

  // 更新当前手势标签（修改后）
  updateCurrentGestureLabel() {
    const selected = this.data.gestureOptions.find(
      item => item.value === this.data.formData.gesture_type
    );
    this.setData({
      currentGestureLabel: selected ? selected.name : '无'  // 使用name字段
    });
  },

  // 地图点击事件处理 - 调用微信地点选择
  onMapTap() {
    console.log('[DEBUG] 开始选择位置...');
    wx.chooseLocation({
      success: (res) => {
        console.log('[DEBUG] 选择位置成功:', res);
        const { longitude, latitude, name } = res;
        
        this.setData({
          'formData.location.lng': longitude,
          'formData.location.lat': latitude,
          locationSelected: true,
          'formData.landmark_name': name || '自定义位置',
          markers: [{
            id: 1,
            longitude,
            latitude,
            iconPath: '/images/marker.jpg',
            width: 30,
            height: 30
          }]
        }, () => {
          // 在setData回调中确保数据已更新后再验证
          console.log('[DEBUG] 地图数据已更新');
          this.checkFormValid();
        });
        
        wx.pageScrollTo({
          scrollTop: 300,
          duration: 300
        });
      },
      fail: (err) => {
        console.error('[DEBUG] 选择位置失败:', err);
        wx.showToast({
          title: '选择位置失败',
          icon: 'none'
        });
      }
    });
  },

  // 重新定位到当前位置
  recenterMap() {
    wx.getLocation({
      type: 'gcj02',
      success: res => {
        const { longitude, latitude } = res;
        this.setData({
          'formData.location.lng': longitude,
          'formData.location.lat': latitude,
          locationSelected: true,
          'formData.landmark_name': '当前位置',
          markers: [{
            id: 1,
            longitude,
            latitude,
            iconPath: '/images/marker.jpg',
            width: 30,
            height: 30
          }]
        }, () => {
          // 确保在回调中验证
          this.checkFormValid();
        });
        
        this.mapCtx.moveToLocation();
      },
      fail: err => {
        console.error('重新定位失败:', err);
        wx.showToast({
          title: '重新定位失败',
          icon: 'none'
        });
      }
    });
  },

  
  // 新增方法 - 选择识别模式
  onCheckModeChange(e) {
    console.log('[模式切换] 选择:', e.detail);

    if (e.detail === 'object') {
      // 如果是物体识别，先显示引导对话框
      this.setData({
        showObjectModeDialog: true,
        'formData.checkMode': e.detail
      });
    }
    this.setData({
      'formData.checkMode': e.detail,
      'formData.object_type': e.detail === 'none' ? 'none' : ''
    });
    this.checkFormValid();
  },

  // 场景选择方法（增加日志）
  onSceneSelect(e) {
    const selected = this.data.sceneOptions[e.detail.value];
    console.log('[场景选择] 选择:', selected);
    this.setData({
      'formData.object_type': "scene-" + selected.value, // 直接使用中文值
      currentSceneLabel: selected.label
    });
    this.checkFormValid();
  },

  // 新增：确认物体识别模式
  confirmObjectMode() {
    this.setData({
      showObjectModeDialog: false
    });
    // 可以在这里添加其他初始化逻辑
  },

  // 新增：取消物体识别模式
  cancelObjectMode() {
    this.setData({
      showObjectModeDialog: false,
      'formData.checkMode': 'none'
    });
  },
  // 选择物体图片（增加日志）
  chooseObjectImage() {
    console.log('[物体识别] 开始选择图片');
    wx.chooseImage({
      count: 1,
      sizeType: ['compressed'],
      success: res => {
        console.log('[物体识别] 已选择图片:', res.tempFilePaths[0]);
        this.uploadObjectImage(res.tempFilePaths[0]);
      },
      fail: err => {
        console.error('[物体识别] 选择图片失败:', err);
      }
    });
  },

   // 上传识别物体（增加确认对话框）
  uploadObjectImage(tempFilePath) {
    console.log('[物体识别] 开始上传:', tempFilePath);
    wx.showLoading({ title: '识别中...' });
    const token = wx.getStorageSync('token') || '';
    
    wx.uploadFile({
      url: `https://${apiDomain}/flask/api/object/recognition`,
      filePath: tempFilePath,
      name: 'image',
      header: {
        'Authorization': `Bearer ${token}`,
        'Content-Type': 'multipart/form-data'
      },
      success: res => {
        console.log('[物体识别] API响应:', res);
        const data = JSON.parse(res.data);
        
        if (data.found) {
          console.log('[物体识别] 识别成功:', data.detections);
          
          // 显示确认对话框
          wx.showModal({
            title: '请确认识别结果',
            content: `系统识别为: ${data.detections.chinese_class_name}\n是否确认使用该结果？`,
            confirmText: '确认',
            cancelText: '重新识别',
            success: (modalRes) => {
              if (modalRes.confirm) {
                // 用户确认，更新数据
                this.setData({
                  tempObjectImage: tempFilePath,
                  objectDetectResult: data.detections.chinese_class_name,
                  'formData.object_type': `object-${data.detections.chinese_class_name}`, // 添加object-前缀，使用中文名
                });
                this.checkFormValid();
                wx.showToast({
                  title: '已确认使用',
                  icon: 'success'
                });
              } else {
                // 用户取消，保留图片但不更新表单
                this.setData({
                  tempObjectImage: tempFilePath,
                  objectDetectResult: '等待确认'
                });
                console.log('[物体识别] 用户取消使用识别结果');
              }
            }
          });
          
        } else {
          console.warn('[物体识别] 未识别到有效物体');
          wx.showToast({ 
            title: '未识别到有效物体', 
            icon: 'none' 
          });
        }
      },
      fail: err => {
        console.error('[物体识别] 识别失败:', err);
        wx.showToast({ 
          title: '识别失败: ' + (err.errMsg || '未知错误'),
          icon: 'none'
        });
      },
      complete: () => {
        console.log('[物体识别] 请求完成');
        wx.hideLoading();
      }
    });
  },


  // 重置物体识别（增加日志）
  resetObject() {
    console.log('[物体识别] 重置识别状态');
    this.setData({
      'formData.object_type': null,
      tempObjectImage: '',
      objectDetectResult: ''
    });
    this.checkFormValid();
  },

  // 描述输入
  onDescriptionInput(e) {
    const description = e.detail.value
    this.setData({
      'formData.description': description,
      descriptionLength: description.length
    })
    this.checkFormValid()
  },

  // 选择图片
  chooseImages() {
    const count = 9 - this.data.tempImages.length;
    if (count <= 0) {
      wx.showToast({
        title: '最多上传9张图片',
        icon: 'none'
      });
      return;
    }

    wx.chooseImage({
      count: count,
      sizeType: ['compressed'],
      sourceType: ['album', 'camera'],
      success: (res) => {
        const tempImages = [...this.data.tempImages, ...res.tempFilePaths];
        this.setData({ tempImages });
        
        // 自动开始上传
        res.tempFilePaths.forEach(path => {
          this.uploadImage(path);
        });
      }
    });
  },

// 上传图片到服务器
uploadImage(tempFilePath) {
  console.group(`[上传] 开始处理: ${tempFilePath}`);
  this.setData({ uploading: true });

  wx.uploadFile({
    url: `https://${apiDomain}/api/files/upload`,
    filePath: tempFilePath,
    name: 'file',
    header: {
      'Authorization': `Bearer ${wx.getStorageSync('token')}`
    },
    success: (res) => {
      try {
        console.log('[响应原始数据]', res);
        const data = JSON.parse(res.data);
        
        // 强化响应验证
        if (!data?.data?.file_url) {
          throw new Error('缺少file_url字段');
        }

        // 处理可能转义的JSON
        const fileInfo = JSON.parse(data.data.file_url.replace(/\\"/g, '"'));
        console.log('[解析文件信息]', fileInfo);

        if (!fileInfo?.id || !fileInfo?.url) {
          throw new Error('无效的文件信息格式');
        }

        // 构建新的图片对象
        const newImage = {
          id: fileInfo.id,
          url: fileInfo.url
        };

        // 更新数据（确保数组格式）
        const currentImages = Array.isArray(this.data.formData.images) ? 
                            this.data.formData.images : [];
        
        this.setData({
          'formData.images': [...currentImages, newImage]
        }, () => {
          console.log('[更新成功] 当前图片列表:', this.data.formData.images);
          console.log('[测试json转义]:', JSON.stringify(this.data.formData.images))
          wx.showToast({ title: '上传成功', icon: 'success' });
        });

      } catch (error) {
        console.error('[处理失败]', error);
        wx.showToast({
          title: `处理失败: ${error.message}`,
          icon: 'none'
        });
      }
    },
    fail: (err) => {
      console.error('[上传失败]', err);
      wx.showToast({
        title: '上传失败，请重试',
        icon: 'none'
      });
    },
    complete: () => {
      this.setData({ uploading: false });
      console.groupEnd();
    }
  });
},

  // 预览图片
  previewImage(e) {
    const { index } = e.currentTarget.dataset;
    wx.previewImage({
      current: this.data.tempImages[index],
      urls: this.data.tempImages
    });
  },

  // 删除图片
  deleteImage(e) {
    const { index } = e.currentTarget.dataset;
    const tempImages = [...this.data.tempImages];
    const savedImages = [...this.data.formData.images];
    
    tempImages.splice(index, 1);
    savedImages.splice(index, 1);
    
    this.setData({ 
      tempImages,
      'formData.images': savedImages
    });
  },
  // 有效范围选择
  onRangeChange(e) {
    const index = parseInt(e.detail.value);
    const selectedOption = this.data.rangeOptions[index];
    
    if (selectedOption.value === 'custom') {
      this.setData({
        selectedRangeIndex: index,
        showRangeInputDialog: true,
        tempCustomRange: ''
      });
    } else {
      this.setData({
        selectedRangeIndex: index,
        'formData.radius': selectedOption.value,
        rangeDisplayText: selectedOption.label // 更新显示文本
      }, () => {
        this.checkFormValid();
      });
    }
  },

  // 确认自定义范围
  confirmCustomRange() {
    const value = parseInt(this.data.tempCustomRange);
    if (value && value > 0) {
      this.setData({
        'formData.radius': value,
        rangeDisplayText: `${value}米`, // 更新显示文本
        showRangeInputDialog: false
      }, () => {
        this.checkFormValid();
      });
    } else {
      wx.showToast({
        title: '请输入有效范围值',
        icon: 'none'
      });
    }
  },

  // 取消自定义范围
  cancelCustomRange() {
    this.setData({
      showRangeInputDialog: false,
      selectedRangeIndex: 0, // 重置为"请选择范围"
      'formData.radius': null
    });
  },

  // 自定义范围输入
  onCustomRangeInput(e) {
    console.log('[调试] 输入事件:', e);
    const value = e.detail;
    console.log('[调试] 输入值:', value);
    
    // 验证输入是否为数字
    if (/^\d*$/.test(value)) {
      console.log('[调试] 输入有效，更新tempCustomRange');
      this.setData({
        tempCustomRange: value
      });
    } else {
      console.warn('[调试] 输入无效，非数字');
    }
  },


   // 关闭群组选择器
  closeGroupPicker() {
    this.setData({ showGroupPicker: false });
  },

 // 打开群组选择器
  async selectGroup() {
    this.setData({ 
      showGroupPicker: true,
      loadingGroups: true
    });
    
    // 显示提示
    wx.showToast({
      title: '只能选择一个自己创建的群组',
      icon: 'none',
      duration: 2000
    });
    
    try {
      await this.loadMyGroups();
    } catch (error) {
      console.error('加载群组失败:', error);
      wx.showToast({
        title: '加载群组失败',
        icon: 'none'
      });
    } finally {
      this.setData({ loadingGroups: false });
    }
  },

  // 加载我的群组
  async loadMyGroups() {
    if (!this.data.hasMoreGroups) {
      console.log('[调试] 已加载全部群组');
      return;
    }
  
    this.setData({ loadingGroups: true });
  
    try {
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/auth/team_info`,
          method: 'GET',
          header: {
            'Authorization': `Bearer ${wx.getStorageSync('token')}`
          },
          data: {
            size: 20,
            lastCursor: this.data.groupNextCursor,
            sort: 'id'
          },
          success: (res) => resolve(res.data),
          fail: reject
        });
      });
  
      console.log('[调试] 完整响应结构', res);
  
      // 修正数据提取路径
      const rawGroups = res.data?.data || []; // 获取原始群组数据
      const nextCursor = res.data?.nextCursor || null;
      
      // 对群组数据进行预处理，添加格式化后的时间
      const processedGroups = rawGroups.map(group => {
        let logo = `https://${apiDomain}${JSON.parse(group.logo).url}`
        return{
        ...group,
        logo: logo,
        formatted_create_time: this.formatDate(group.create_time) // 添加格式化后的时间字段
        }
      });
  
      console.log('[调试] 获取到的群组', {
        count: processedGroups.length,
        sample: processedGroups.slice(0, 3), // 打印前3条样本（包含格式化时间）
        nextCursor
      });
  
      this.setData({
        availableGroups: [...this.data.availableGroups, ...processedGroups], // 使用处理后的数据
        groupNextCursor: nextCursor,
        hasMoreGroups: !!nextCursor
      });
  
    } catch (error) {
      console.error('[调试] 加载失败', error);
      wx.showToast({
        title: '加载群组失败',
        icon: 'none'
      });
    } finally {
      this.setData({ loadingGroups: false });
    }
  },

  // 单选群组
  selectSingleGroup(e) {
    const group = e.currentTarget.dataset.group;
    
    // 更新选中群组
    this.setData({ 
      selectedGroup: group,
      'formData.team_id': group.id
    });
    
    // 显示选中提示
    wx.showToast({
      title: `已选择: ${group.name}`,
      icon: 'none',
      duration: 1000
    });
    
    // 直接关闭弹窗
    this.closeGroupPicker();
    
    // 验证表单
    this.checkFormValid();
  },

  // 移除群组
  removeGroup() {
    this.setData({
      selectedGroup: null,
      'formData.team_id': null
    });
    this.checkFormValid();
    
    wx.showToast({
      title: '已移除群组',
      icon: 'none',
      duration: 800
    });
  },

  // 格式化群组的创建时间
  formatDate(dateStr) {
    if (!dateStr) return '未知时间';
    
    try {
      const date = new Date(dateStr);
      return `${date.getFullYear()}-${this.padZero(date.getMonth()+1)}-${this.padZero(date.getDate())} ${this.padZero(date.getHours())}:${this.padZero(date.getMinutes())}`;
    } catch (e) {
      console.warn('时间格式化异常:', e);
      return dateStr; // 返回原始字符串作为fallback
    }
  },
  
  // 确保padZero方法存在
  padZero(num) {
    return num < 10 ? `0${num}` : num;
  },

 // 人脸识别开关
  onFaceVerifyChange(e) {
    const needVerify = e.detail ? 1 : 0
    
    if (needVerify === 1) {
      wx.showModal({
        title: '重要提示',
        content: '开启后，参与者需先完成人脸注册才能参加挑战。确认开启吗？',
        success: (res) => {
          const newValue = res.confirm ? 1 : 0;
          this.setData({
            'formData.needFaceVerify': newValue
          }, () => {
            // 在回调中确保数据已更新
            this.checkFormValid();
            if (newValue) {
              wx.showToast({ title: '已开启人脸验证', icon: 'success' });
            }
          });
        }
      });
    } else {
      this.setData({
        'formData.needFaceVerify': 0
      }, () => {
        this.checkFormValid();
      });
    }
  },

  // 初始化时间选择器数据
  initTimeArray() {
    const hours = Array.from({ length: 24 }, (_, i) => i.toString().padStart(2, '0'))
    const minutes = Array.from({ length: 60 }, (_, i) => i.toString().padStart(2, '0'))
    const seconds = ['00']
    
    this.setData({
      timeArray: [hours, minutes, seconds]
    })
  },

    // 显示开始时间选择器
  showStartPicker() {
    this.setData({
      showStartPicker: true,
      currentStartDate: this.data.startDateTime 
        ? new Date(this.data.startDateTime.replace(/-/g, '/')).getTime()
        : new Date().getTime()
    });
  },

  // 显示结束时间选择器
  showEndPicker() {
    this.setData({
      showEndPicker: true,
      currentEndDate: this.data.endDateTime 
        ? new Date(this.data.endDateTime.replace(/-/g, '/')).getTime()
        : new Date().getTime()
    });
  },

   
// 开始时间确认（简化版）
onStartConfirm(e) {
  console.group('[调试] 开始时间确认');
  console.log('原始选择值:', e.detail);
  
  const date = new Date(e.detail);
  const formatted = `${date.getFullYear()}-${this.padZero(date.getMonth() + 1)}-${this.padZero(date.getDate())} ${this.padZero(date.getHours())}:${this.padZero(date.getMinutes())}:00`;
  
  console.log('格式化显示时间:', formatted);
  
  this.setData({
    startDateTime: formatted,
    'formData.startTime': formatted, // 直接使用格式化时间
    showStartPicker: false
  }, () => {
    console.log('更新后的数据:', {
      startDateTime: this.data.startDateTime,
      formDataStartTime: this.data.formData.startTime
    });
    console.groupEnd();
    this.checkFormValid();
  });
},

// 结束时间确认（简化版）
onEndConfirm(e) {
  console.group('[调试] 结束时间确认');
  console.log('原始选择值:', e.detail);
  
  const date = new Date(e.detail);
  const formatted = `${date.getFullYear()}-${this.padZero(date.getMonth() + 1)}-${this.padZero(date.getDate())} ${this.padZero(date.getHours())}:${this.padZero(date.getMinutes())}:00`;
  
  // 验证结束时间必须大于开始时间
  if (this.data.startDateTime && new Date(e.detail) <= new Date(this.data.startDateTime.replace(/-/g, '/'))) {
    console.warn('结束时间必须大于开始时间');
    wx.showToast({
      title: '结束时间必须大于开始时间',
      icon: 'none'
    });
    console.groupEnd();
    return;
  }
  
  this.setData({
    endDateTime: formatted,
    'formData.endTime': formatted, // 直接使用格式化时间
    showEndPicker: false
  }, () => {
    console.log('更新后的数据:', {
      endDateTime: this.data.endDateTime,
      formDataEndTime: this.data.formData.endTime
    });
    console.groupEnd();
    this.checkFormValid();
  });
},


  // 取消选择
  onPickerCancel() {
    this.setData({
      showStartPicker: false,
      showEndPicker: false
    });
  },

  // 补零函数
  padZero(num) {
    return num < 10 ? `0${num}` : num;
  },


  // 表单验证（带详细验证信息）
  checkFormValid() {
    const { title, formData, locationSelected } = this.data;
    
    // 验证规则（更新后包含描述验证）
    const validations = {
      title: {
        valid: !!title && title.trim() !== '',
        message: '请填写挑战标题'
      },
      location: {
        valid: locationSelected && formData.landmark_name,
        message: '请选择打卡地点'
      },
      radius: {
        valid: formData.radius !== null && formData.radius !== undefined && formData.radius > 0,
        message: '请选择或输入有效范围'
      },
      description: {
        valid: !!formData.description && formData.description.trim() !== '',
        message: '请填写挑战描述'
      },
      startTime: {
        valid: !!formData.startTime && formData.startTime.trim() !== '',
        message: '请设置开始时间'
      },
      endTime: {
        valid: !!formData.endTime && formData.endTime.trim() !== '',
        message: '请设置结束时间'
      },
      timeOrder: {
        valid: !formData.startTime || !formData.endTime || 
              new Date(formData.endTime) > new Date(formData.startTime),
        message: '结束时间必须晚于开始时间'
      }
    };

    // 检查所有必填项
    const isValid = Object.values(validations).every(v => v.valid);
    
    // 收集错误信息并拼接成字符串
    const errorMessages = Object.entries(validations)
      .filter(([_, v]) => !v.valid)
      .map(([_, v]) => v.message);
      
    const errorMessageStr = errorMessages.join('，');

    this.setData({ 
      formValid: isValid,
      validationErrors: errorMessages, // 保留数组形式用于调试
      validationErrorText: errorMessageStr // 新增：拼接好的字符串
    }, () => {
      console.log('[表单验证完成]', {
        isValid,
        errors: errorMessages,
        currentData: {
          title,
          description: formData.description,
          location: formData.location,
          startTime: formData.startTime,
          endTime: formData.endTime,
          range: formData.radius
        }
      });
    });
  },

  async submitChallenge() {
    if (!this.data.formValid || this.data.submitting) {
      console.log('[提交阻止] 表单未验证或正在提交中', {
        formValid: this.data.formValid,
        submitting: this.data.submitting
      });
      return;
    }
  
    const token = wx.getStorageSync('token');
    this.setData({ submitting: true });
  
    // 准备提交数据（严格遵循接口字段）
    const submitData = {
      title: this.data.title,
      description: this.data.formData.description,
      object_type: this.data.formData.object_type,
      gesture_type: this.data.formData.gesture_type,
      landmark_name: this.data.formData.landmark_name,
      radius: this.data.formData.radius,
      location: this.data.formData.location,
      team_id: this.data.formData.team_id,
      start_time: this.data.formData.startTime,
      end_time: this.data.formData.endTime,
      need_face_verify: this.data.formData.needFaceVerify,
      images: JSON.stringify(this.data.formData.images),
    };
  
    // 调试输出完整提交数据
    console.group('[提交调试] 准备提交的数据');
    console.log('完整提交数据:', JSON.parse(JSON.stringify(submitData)));
    console.log('Token:', token ? '存在' : '不存在');
    console.log('API域名:', apiDomain);
    console.groupEnd();
  
    try {
      console.log('[请求开始] 正在发送请求...');
      const startTime = Date.now();
      
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/challenges/create`, // 使用配置的apiDomain
          method: 'POST',
          header: {
            'Authorization': `Bearer ${token}`,
            'Content-Type': 'application/json'
          },
          data: submitData,
          success: (res) => {
            console.log('[请求成功] 响应数据:', res);
            resolve(res);
          },
          fail: (err) => {
            console.error('[请求失败] 错误详情:', err);
            reject(err);
          }
        });
      });
  
      const responseTime = Date.now() - startTime;
      console.log(`[请求完成] 耗时: ${responseTime}ms`, res);
  
      if (res.data.code === "200" || res.data.code === '0') {
        console.log('[提交成功] 服务器返回成功');
        wx.showToast({ 
          title: '发布成功', 
          icon: 'success',
          success: () => {
            setTimeout(() => {
              console.log('[导航返回] 返回上一页');
              wx.navigateBack();
            }, 1500);
          }
        });
      } else {
        console.warn('[提交异常] 服务器返回非200状态', res.data);
        throw new Error(res.data.msg || '发布失败');
      }
    } catch (error) {
      console.error('[提交错误] 捕获到异常:', error);
      wx.showToast({ 
        title: error.message, 
        icon: 'none',
        duration: 3000 
      });
    } finally {
      console.log('[提交结束] 清除提交状态');
      this.setData({ submitting: false });
    }
  },
  
  // 阻止事件冒泡
  stopPropagation(e) {
    e.stopPropagation();
  },

  // 辅助方法 - 时间格式化
  formatISOTime(timeStr) {
    if (!timeStr) return '';
    
    // 处理已经重复的格式
    if (timeStr.includes('T') && timeStr.split('T').length > 2) {
      const parts = timeStr.split('T');
      return `${parts[0]}T${parts[2]}`;
    }
    
    // 处理标准格式
    if (timeStr.includes('T')) {
      return timeStr;
    }
    
    // 处理普通时间字符串 (格式: "2023-03-14 12:30:45")
    if (timeStr.includes(' ')) {
      const [datePart, timePart] = timeStr.split(' ');
      return `${datePart}T${timePart}Z`;
    }
    
    return timeStr;
  },
  hideHint() {
    this.setData({
      locationSelected: true
    })
  },
  navigateBack() {
    wx.navigateBack()
  },

  setTheme(themeIndex) {
    // 主题设置逻辑（根据实际需求实现）
  }
})