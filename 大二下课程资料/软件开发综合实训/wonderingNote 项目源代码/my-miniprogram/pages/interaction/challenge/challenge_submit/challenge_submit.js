const { apiDomain } = require("../../../../config");

Page({
  data: {
    showCamera: false, // 新增控制摄像头显示的状态
    cameraMode: 'normal', // 'normal' | 'face' | 'gesture'
    cameraPosition: 'front', // 摄像头位置
    id: '',
    challenge: null,
    remainTimeText: '',
    gestureImage: '',
    landmarkImage: '',
    faceImage: '',
    distance: null,
    validationResult: false,
    loading: false,
    showFaceVerify: false,
    isFaceVerified: false,
    mapContext: null,
    markers: [],
    locationVerified: false,
    locationResult: null,
    userLocation: null, // 存储用户当前位置
    challengeLocation: null, // 存储挑战要求的位置
    polygons: [{
      points: [],
      strokeWidth: 2,
      strokeColor: '#1890ff80',
      fillColor: '#1890ff20'
    }],
    gestureVerified: false,
    landmarkVerified: false,
    gestureResult: null,
    sceneResult: null,
    objectResult: null,
    isFaceDetecting: false,       // 是否正在检测人脸
    faceDetectionInterval: null,   // 人脸检测定时器
    randomGestureNumber: 0,       // 随机生成的手势数字
    showGestureVerify: false,     // 是否显示手势验证界面
    gestureVerifyImage: '',        // 手势验证图片
    gestureVerifyResult: null,      // 手势验证结果
    faceVerifiedOnly: false, // 仅人脸验证通过
    gestureVerified: false,  // 手势验证通过
    isFaceVerified: false,    // 双重验证通过
    cameraContext: null, // 全局唯一的摄像头上下文
    sceneMappings: {
      // 英文到中文
      enToCn: {
        'sea': '海洋',
        'forest': '森林',
        'mountain': '山脉',
        'street': '街道',
        'buildings': '建筑'
      },
      // 中文到英文
      cnToEn: {
        '海洋': 'sea',
        '森林': 'forest',
        '山脉': 'mountain',
        '街道': 'street',
        '建筑': 'buildings'
      }
    },
    gestureMappings: {
      enToCn: {
        'None': '无手势',
        'Closed_Fist': '握拳',
        'Open_Palm': '张开手掌',
        'Pointing_Up': '手指向上',
        'Thumb_Down': '拇指向下',
        'Thumb_Up': '点赞',
        'Victory': '胜利手势',
        'ILoveYou': '我爱你手势'
      },
      cnToEn: {
        '握拳': 'Closed_Fist',
        '张开手掌': 'Open_Palm',
        '手指向上': 'Pointing_Up',
        '拇指向下': 'Thumb_Down',
        '点赞': 'Thumb_Up',
        '胜利手势': 'Victory',
        '我爱你手势': 'ILoveYou'
      },
      cnToEmoji: {
        '握拳': '👊',
        '张开手掌': '🖐️',
        '手指向上': '👆',
        '拇指向下': '👎',
        '点赞': '👍',
        '胜利手势': '✌️',
        '我爱你手势': '🤟'
      }
    },
    evidence: [],
    canSubmit: false, // 新增控制按钮状态的变量
    aiVerified: false, // 新增AI验证状态
    lastUploadType: '',
    evidenceCount: 0
  },

  onLoad(options) {
    console.log('页面参数:', options); // 调试用
    
    // 修改这里：同时兼容 id 和 challengeId 参数
    const challengeId = options.id || options.challengeId;
    if (!challengeId) {
      console.error('未收到挑战ID参数');
      wx.showToast({ title: '参数错误', icon: 'none' });
      return setTimeout(() => wx.navigateBack(), 1500);
    }
  
    this.setData({ id: challengeId }, () => {
      this.fetchChallengeDetail();
      
    });
    
    this.setData({ mapContext: wx.createMapContext('verifyMap') });
    this.initCameraContext();
    
  },
  
  initCameraContext() {
    if (!this.data.cameraContext) {
      this.setData({
        cameraContext: wx.createCameraContext()
      });
    }
  },
  // 显示摄像头（统一入口）
  showCameraView(mode = 'normal', position = 'front') {
    this.setData({
      showCamera: true,
      cameraMode: mode,
      cameraPosition: position
    }, () => {
      // 确保DOM更新完成
      setTimeout(() => {
        this.initCameraContext();
      }, 300);
    });
  },

  // 隐藏摄像头
  hideCameraView() {
    this.setData({ showCamera: false });
  },
  watchDataChange: function() {
    const { 
      evidence,
      challenge,
      locationVerified,
      isFaceVerified
    } = this.data;

    // 检查是否满足基本提交条件
    const basicCheck = locationVerified && 
      (!challenge.need_face_verify || isFaceVerified);

    // 检查是否有上传所有需要的图片
    const hasGestureImage = !challenge.gesture_type || 
      evidence.some(e => e.type === 'gesture');
    const hasSpecialImage = !challenge.specialRequirement || 
      evidence.some(e => e.type === 'special');

    // 检查所有验证是否通过
    const allVerified = (!challenge.gesture_type && this.data.gestureVerified) &&
      (!challenge.specialRequirement && this.data.landmarkVerified) &&
      (!challenge.need_face_verify && this.data.isFaceVerified);

    this.setData({
      canSubmit: basicCheck && hasGestureImage && hasSpecialImage,
      aiVerified: allVerified
    });
  },
  // 获取挑战详情
  async fetchChallengeDetail() {
    wx.showLoading({ title: '加载中...' });
    console.log('[DEBUG] 开始获取挑战详情');
    
    try {
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/challenges/${this.data.id}`,
          success: resolve,
          fail: reject
        });
      });
      
      console.log('[DEBUG] 接口响应数据:', res.data);
      
      if (res.data.code === "0" || res.data.code === "200") {
        const processedData = this.processChallengeData(res.data.data);
        console.log('[DEBUG] 处理后数据:', processedData);
        
        // 先设置基础数据
        this.setData({ 
          challenge: {
            ...processedData,
            images: processedData.images // 确保images是数组
          } 
        }, () => {
          console.log('[DEBUG] 基础数据设置完成');
          
          // 只有图片数量>0时才下载
          if (processedData.images && processedData.images.length > 0) {
            console.log('[DEBUG] 开始下载图片...');
            this.downloadImages(processedData.images).then(downloadedImages => {
              console.log('[DEBUG] 图片下载完成:', downloadedImages);
              const validImages = downloadedImages.filter(img => !img.error);
              console.log('[下载的]')
              this.setData({
                'challenge.images': validImages
              }, () => {
                this.initMapData();
              });
            });
          } else {
            console.log('[DEBUG] 无图片需要下载');
            this.initMapData();
          }
        });
      } else {
        throw new Error(res.data.msg || '获取数据失败');
      }
    } catch (err) {
      console.error('[ERROR] 请求失败:', err);
      wx.showToast({ title: '网络错误', icon: 'none' });
    } finally {
      wx.hideLoading();
      console.log('[页面当前数据]', this.data)
      console.log('[页面当前的封面]', this.data.challenge.coverImage)
    }
  },
  
  // 下载图片方法
// 修改后的下载图片方法
async downloadImages(images) {
  console.log('[DEBUG] 开始下载图片，数量:', images.length);
  
  if (!images || images.length === 0) {
    console.log('[DEBUG] 无图片需要下载');
    return [];
  }

  const results = [];
  
  for (let i = 0; i < images.length; i++) {
    const img = images[i];
    console.log(`[DEBUG] 正在处理第 ${i+1}/${images.length} 张图片`, img);
    
    try {
      // 使用您提供的下载方法
      const result = await this.downloadImage(img);
      
      console.log(`[DEBUG] 下载成功 第 ${i+1} 张`, result);
      
      // 立即更新UI显示
      this.setData({
        [`challenge.images[${i}].localPath`]: result.url,
        [`challenge.images[${i}].loaded`]: true,
        [`challenge.images[${i}].error`]: false
      });

      results.push({
        ...img,
        localPath: result.url,
        loaded: true,
        isTemp: result.isTemp
      });
    } catch (error) {
      console.error(`[ERROR] 处理失败 第 ${i+1} 张`, error);
      
      // 更新错误状态
      this.setData({
        [`challenge.images[${i}].error`]: true,
        [`challenge.images[${i}].errorMsg`]: error.message || '处理失败'
      });

      results.push({
        ...img,
        error: true,
        errorMsg: error.message || '处理失败'
      });
    }
  }
  
  return results;
},
// 您的下载方法（稍作优化）
async downloadImage(fileInfo) {
  try {
    // 提取文件ID（支持多种格式）
    const fileId = typeof fileInfo === 'string' ? 
                 (fileInfo.match(/\d+/)?.[0] || fileInfo) : 
                 (fileInfo.id || fileInfo.url?.match(/\/(\d+)\//)?.[1]);
    
    if (!fileId) throw new Error('无法获取文件ID');

    console.log('[DOWNLOAD] 正在下载文件ID:', fileId);
    
   // 直接下载文件
   const { tempFilePath } = await new Promise((resolve, reject) => {
    wx.downloadFile({
      url: `https://${apiDomain}/api/files/${fileId}/download`,
      success: (res) => res.statusCode === 200 ? resolve(res) : reject(res),
      fail: reject
    });
  });

    return {
      id: fileId,
      url: tempFilePath,
      isTemp: true
    };

  } catch (error) {
    console.error('[DOWNLOAD] 下载失败:', error);
    throw error; // 继续向上抛出错误
  }
},

processChallengeData(data) {
  // 解析images字段（支持多种格式）
  let images = [];
  try {
    const parsedData = typeof data.images === 'string' ? JSON.parse(data.images) : data.images;
    
    console.log("==========", parsedData)
    // 处理数组格式
    if (Array.isArray(parsedData)) {
      images = parsedData.map(img => ({
        id: img.id || Math.random().toString(36).substring(7),
        url: img.url.startsWith('https') ? img.url : `https://${apiDomain}${img.url}`,
        originalUrl: img.url.startsWith('https') ? img.url : `https://${apiDomain}${img.url}`,
        loaded: false,
        error: false
      }));
    } 
    // 处理单对象格式
    else if (parsedData && parsedData.url) {
      images = [{
        id: parsedData.id || Math.random().toString(36).substring(7),
        url: parsedData.url.startsWith('https') ? parsedData.url : `https://${apiDomain}${parsedData.url}`,
        originalUrl: parsedData.url.startsWith('https') ? parsedData.url : `https://${apiDomain}${parsedData.url}`,
        loaded: false,
        error: false
      }];
    }
  } catch (e) {
    console.warn('解析images失败:', e);
    // 如果解析失败，尝试直接使用
    if (typeof data.images === 'string' && data.images.startsWith('https')) {
      images = [{
        id: Math.random().toString(36).substring(7),
        url: data.images,
        originalUrl: data.images,
        loaded: false,
        error: false
      }];
    } else if (typeof data.images === 'string' && data.images.startsWith('/')) {
      images = [{
        id: Math.random().toString(36).substring(7),
        url: `https://${apiDomain}${data.images}`,
        originalUrl: `https://${apiDomain}${data.images}`,
        loaded: false,
        error: false
      }];
    }
  }
  let specialRequirement = null;
  if (data.object_type) {
    const [type, value] = data.object_type.split('-');
    specialRequirement = {
      type,  // scene或object
      value, // 需要识别的具体内容
      fullType: data.object_type
    };
  }

  let gesture_type = data.gesture_type
  if (gesture_type === '不设置'){
    gesture_type = ''
  }
  return {
    ...data,
    gesture_type: gesture_type,
    images, // 存储解析后的图片数组
    coverImage: images[0]?.url || '/static/images/default-challenge-cover.jpg',
    location: {
      lat: parseFloat(data.location.lat),
      lng: parseFloat(data.location.lng)
    },
    specialRequirement, // 特殊打卡要求
    create_time: this.formatTime(data.create_time),
    start_time: this.formatTime(data.start_time),
    end_time: this.formatTime(data.end_time)
  };
},

  // 2. 修改 initMapData 方法
 // 修改initMapData方法，保存挑战位置
initMapData() {
  console.log('初始化地图数据，当前挑战:', this.data.challenge);
  
  if (!this.data.challenge?.location) {
    console.error('缺少位置信息');
    return;
  }

  // 保存挑战位置
  this.setData({
    challengeLocation: this.data.challenge.location
  });

  const { lat, lng } = this.data.challenge.location;
  const radius = this.data.challenge.radius / 111000;
  
  console.log('中心点:', lat, lng, '半径(度):', radius);
  
  const polygon = {
    points: this.generateCirclePolygon(lat, lng, radius),
    strokeWidth: 2,
    strokeColor: '#1890ff',
    fillColor: '#1890ff20'
  };

  console.log('生成的多边形:', polygon);
  
  this.setData({
    polygons: [polygon],
    markers: [{
      id: 0,
      latitude: lat,
      longitude: lng,
      iconPath: '/assets/images/marker.jpg',
      width: 30,
      height: 30
    }]
  });
},
  
generateCirclePolygon(lat, lng, radius, points = 36) {
  const coords = [];
  for (let i = 0; i <= points; i++) { // 注意这里是 <= 确保闭合
    const angle = (i * 2 * Math.PI) / points;
    coords.push({
      latitude: parseFloat((lat + radius * Math.cos(angle)).toFixed(6)),
      longitude: parseFloat((lng + radius * Math.sin(angle)).toFixed(6))
    });
  }
  return coords;
},

// 计算两点间距离(米)
calculateDistance(lat1, lng1, lat2, lng2) {
  const R = 6371000; // 地球半径(米)
  const dLat = (lat2 - lat1) * Math.PI / 180;
  const dLng = (lng2 - lng1) * Math.PI / 180;
  const a = 
    Math.sin(dLat/2) * Math.sin(dLat/2) +
    Math.cos(lat1 * Math.PI / 180) * 
    Math.cos(lat2 * Math.PI / 180) * 
    Math.sin(dLng/2) * Math.sin(dLng/2);
  const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
  return Math.round(R * c);
},

// 提交位置验证到服务器
async submitLocationVerification(latitude, longitude) {
  try {
    // 强制调试输出（务必保留）
    console.group('[强制调试] 位置验证请求');
    console.log('收到的坐标:', { latitude, longitude });

    // 确保数据结构完全匹配API要求
    const requestData = {
      location: {  // 字段名必须为location
        lng: parseFloat(longitude), // 字段名必须为lng
        lat: parseFloat(latitude)   // 字段名必须为lat
      }
    };
    console.log('最终请求体:', JSON.stringify(requestData, null, 2));

    const res = await new Promise((resolve, reject) => {
      wx.request({
        url: `https://${apiDomain}/api/challenges/${this.data.id}/location_submit`,
        method: 'POST',
        header: { 
          'Content-Type': 'application/json',
          'Authorization': `Bearer ${wx.getStorageSync('token')}`
        },
        data: requestData, // 确保传入了格式化后的数据
        success: (res) => {
          console.log('完整响应:', res); // 打印完整响应
          resolve(res.data);
        },
        fail: (err) => {
          console.error('请求失败:', err);
          reject(err);
        }
      });
    });

    return res;
  } catch (error) {
    console.error('验证失败:', error);
    throw error;
  } finally {
    console.groupEnd(); // 结束调试分组
  }
},
// 修改uploadGesture方法
async uploadGesture() {
  try {
    // 1. 选择图片
    const { tempFilePaths } = await wx.chooseImage({
      count: 1,
      sizeType: ['compressed']
    });
    
    wx.showLoading({ title: '验证中...', mask: true });
    
    // 2. 获取挑战要求的手势类型（添加默认值）
    const requiredGesture = this.data.challenge?.gesture_type || '';
    
    // 3. 先上传图片（无论验证结果如何）
    const uploadData = await new Promise((resolve, reject) => {
      wx.uploadFile({
        url: `https://${apiDomain}/api/files/upload`,
        filePath: tempFilePaths[0],
        name: 'file',
        header: { 
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'multipart/form-data'
        },
        success: (res) => {
          try {
            const data = typeof res.data === 'string' ? JSON.parse(res.data) : res.data;
            if (res.statusCode === 200) {
              resolve(data);
            } else {
              reject(new Error(`HTTP ${res.statusCode}: ${data.msg || '上传失败'}`));
            }
          } catch (e) {
            reject(new Error('响应数据解析失败'));
          }
        },
        fail: (err) => {
          reject(new Error(`上传失败: ${err.errMsg}`));
        }
      });
    });

    // 4. 解析file_url并保存证据（无论验证结果如何）
    let fileInfo = {};
    try {
      fileInfo = JSON.parse(uploadData.data.file_url);
      console.log('解析后的file_url:', fileInfo);
      
      // 添加到evidence数组
      const newEvidence = [...this.data.evidence];
      if (newEvidence.length >= 2) {
        // 如果已满2条，替换
        let index = 0
        if (this.data.lastUploadType === 'gesture') {
          index = 1
        }
        newEvidence[index] = {
          id: fileInfo.id,
          url: fileInfo.url,
          type: 'gesture',
          uploadTime: new Date().toISOString(),
          gestureType: requiredGesture
        };
      } else {
        // 如果不足2条，直接添加
        newEvidence.push({
          id: fileInfo.id,
          url: fileInfo.url,
          type: 'gesture',
          uploadTime: new Date().toISOString(),
          gestureType: requiredGesture
        });
      }
      this.setData({ 
        lastUploadType: 'gesture',
        evidence: newEvidence,
        gestureImage: `https://${apiDomain}${fileInfo.url}`
      });
      console.log('[更新后的evidence]', this.data.evidence)
    } catch (e) {
      console.error('解析file_url失败:', e);
      throw new Error('文件信息解析失败');
    }

    // 5. 如果有手势要求，则进行验证
    if (requiredGesture) {
      try {
        const gestureRes = await this.verifyGesture(tempFilePaths[0]);
        console.log('手势识别结果:', gestureRes);
        
        const primaryDetection = gestureRes.primaryDetection;
        const recognizedGesture = primaryDetection?.gesture;
        const confidence = primaryDetection?.confidence || 0;
        
        const gestureMappings = this.data.gestureMappings || {};
        const recognizedCn = gestureMappings.enToCn?.[recognizedGesture] || recognizedGesture;
        const requiredEn = gestureMappings.cnToEn?.[requiredGesture];
        
        if (requiredEn && recognizedGesture === requiredEn && confidence >= 0.5) {
          this.setData({ 
            gestureVerified: true,
            gestureResult: {
              ...gestureRes,
              displayText: `验证通过: ${requiredGesture}` +
                         `(置信度:${(confidence*100).toFixed(1)}%)`
            }
          });
          this.watchDataChange();
          wx.showToast({ 
            title: `手势验证通过: ${requiredGesture}`, 
            icon: 'success',
            duration: 2000
          });
        } else {
          wx.showToast({ 
            title: `手势验证未通过`, 
            icon: 'none',
            duration: 2000
          });
        }
      } catch (verifyError) {
        console.error('[GESTURE_VERIFY_ERROR]', verifyError);
        // 验证失败不影响图片已上传
      }
    } else {
      // 没有手势要求，直接标记为已验证
      this.setData({ gestureVerified: true });
    }
  } catch (error) {
    console.error('[GESTURE_ERROR]', error);
    wx.showToast({ 
      title: error.message.includes('undefined') 
        ? '手势验证系统错误' 
        : error.message || '手势验证失败', 
      icon: 'none',
      duration: 3000
    });
  } finally {
    wx.hideLoading();
  }
},
// 新增手势验证方法
async verifyGesture(imagePath) {
  try {
    const res = await new Promise((resolve, reject) => {
      wx.uploadFile({
        url: `https://${apiDomain}/flask/api/gesture/semantic`,
        filePath: imagePath,
        name: 'image',
        header: { 
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'multipart/form-data'
        },
        success: (res) => {
          console.log("-==============",res)
          if (res.statusCode !== 200 ) {
            reject(new Error(`API请求失败(HTTP ${res.statusCode})`));
            return;
          }
          resolve(res);
        },
        fail: (err) => {
          reject(new Error(`网络请求失败: ${err.errMsg}`));
        }
      });
    });

    // 解析响应数据
    console.log('[DEBUG] 手势API原始响应:', res);
    
    let data;
    try {
      data = typeof res.data === 'string' ? JSON.parse(res.data) : res.data;
    } catch (e) {
      console.error('响应数据解析失败:', res.data);
      throw new Error('API返回了无效的JSON数据');
    }
    
    console.log('[DEBUG] 解析后的手势数据:', data);

    // 验证响应格式
    if (data.code !== 0) {
      throw new Error(data.message || '手势识别失败');
    }

    // 检查是否有识别结果
    if (!data.found || !data.detections || !data.detections.length) {
      throw new Error('未能识别出手势');
    }

    // 取第一个检测结果（假设API可能返回多个手的检测结果）
    const primaryDetection = data.detections[0];
    if (primaryDetection.gesture === "None") {
      throw new Error('未能识别出有效手势');
    }

    return {
      ...data,
      primaryDetection // 将主要检测结果也返回
    };
  } catch (error) {
    console.error('[GESTURE_VERIFY_ERROR]', error);
    throw new Error(`手势验证失败: ${error.message}`);
  }
},

// 验证特殊打卡要求
async verifySpecialRequirement() {
  try {
    // 1. 选择图片
    const { tempFilePaths } = await wx.chooseImage({
      count: 1,
      sizeType: ['compressed']
    });

    wx.showLoading({ title: '验证中...', mask: true });

    // 2. 获取挑战的特殊要求
    const { specialRequirement } = this.data.challenge;

    // 3. 先上传图片（无论验证结果如何）
    const uploadData = await new Promise((resolve, reject) => {
      wx.uploadFile({
        url: `https://${apiDomain}/api/files/upload`,
        filePath: tempFilePaths[0],
        name: 'file',
        header: { 
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'multipart/form-data'
        },
        success: (res) => {
          try {
            const data = typeof res.data === 'string' ? JSON.parse(res.data) : res.data;
            if (res.statusCode === 200) {
              resolve(data);
            } else {
              reject(new Error(`HTTP ${res.statusCode}: ${data.msg || '上传失败'}`));
            }
          } catch (e) {
            reject(new Error('响应数据解析失败'));
          }
        },
        fail: (err) => {
          reject(new Error(`上传失败: ${err.errMsg}`));
        }
      });
    });

    // 4. 解析file_url并保存证据（无论验证结果如何）
    let fileInfo = {};
    try {
      fileInfo = JSON.parse(uploadData.data.file_url);
      console.log('解析后的file_url:', fileInfo);
      
      const newEvidence = [...this.data.evidence];
      if (newEvidence.length >= 2) {
        // 如果已满2条，替换
        let index = 0
        if(this.data.lastUploadType === 'special'){
          index = 1
        }
        newEvidence[index] = {
          id: fileInfo.id,
          url: fileInfo.url,
          type: 'special',
          uploadTime: new Date().toISOString()
        };
      } else {
        // 如果不足2条，直接添加
        newEvidence.push({
          id: fileInfo.id,
          url: fileInfo.url,
          type: 'special',
          uploadTime: new Date().toISOString()
        });
      }
      
      this.setData({ 
        lastUploadType: 'special',
        evidence: newEvidence,
        specialImage: `https://${apiDomain}${fileInfo.url}`
      });
      console.log('[更新后的evidence]', this.data.evidence)
    } catch (e) {
      console.error('解析file_url失败:', e);
      throw new Error('文件信息解析失败');
    }

    // 5. 如果有特殊要求，则进行验证
    if (specialRequirement) {
      try {
        let verifyResult;
        if (specialRequirement.type === 'scene') {
          verifyResult = await this.verifySceneRequirement(
            tempFilePaths[0], 
            specialRequirement.value
          );
        } else if (specialRequirement.type === 'object') {
          verifyResult = await this.verifyObjectRequirement(
            tempFilePaths[0],
            specialRequirement.value
          );
        }

        if (verifyResult?.success) {
          this.setData({ 
            landmarkVerified: true,
            sceneResult: verifyResult?.sceneResult,
            objectResult: verifyResult?.objectResult,
            sceneVerifyResult: verifyResult?.sceneResult ? {
              ...verifyResult.sceneResult,
              displayText: `验证通过: ${specialRequirement.value}` +
                         `(置信度:${(verifyResult.sceneResult.confidence*100).toFixed(1)}%)`
            } : null
          });
          this.watchDataChange();
          wx.showToast({ 
            title: `验证通过: ${specialRequirement.value}`, 
            icon: 'success',
            duration: 2000
          });
        } else {
          wx.showToast({ 
            title: '特殊打卡验证未通过', 
            icon: 'none',
            duration: 2000
          });
        }
      } catch (verifyError) {
        console.error('[SPECIAL_VERIFY_ERROR]', verifyError);
        // 验证失败不影响图片已上传
      }
    } else {
      // 没有特殊要求，直接标记为已验证
      this.setData({ landmarkVerified: true });
    }
  } catch (error) {
    console.error('[SPECIAL_REQUIREMENT_ERROR]', error);
    wx.showToast({
      title: error.message || '特殊打卡验证失败',
      icon: 'none',
      duration: 3000
    });
  } finally {
    wx.hideLoading();
  }
},

// 场景类型验证
async verifySceneRequirement(imagePath, cnSceneName) {
  try {
    // 1. 中文场景转英文标识
    const enSceneName = this.data.sceneMappings.cnToEn[cnSceneName];
    if (!enSceneName) {
      throw new Error('不支持该场景类型');
    }

    console.log('[DEBUG] 开始场景验证，目标场景:', {
      中文: cnSceneName,
      英文: enSceneName
    });

    // 2. 调用API
    const res = await new Promise((resolve, reject) => {
      wx.uploadFile({
        url: `https://${apiDomain}/flask/api/scene/recognition`,
        filePath: imagePath,
        name: 'image',
        header: { 
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'multipart/form-data'
        },
        success: resolve,
        fail: reject
      });
    });

    // 3. 解析响应数据
    console.log('[DEBUG] 场景API原始响应:', res);
    const data = typeof res.data === 'string' ? JSON.parse(res.data) : res.data;
    console.log('[DEBUG] 解析后的场景数据:', data);

    // 4. 验证响应格式
    if (data.code !== 0 && data.code !== "0") {
      throw new Error(data.message || '场景识别失败');
    }

    // 5. 检查场景匹配
    if (!data.found || !data.detections || data.detections.scene !== enSceneName) {
      throw new Error(`未检测到${cnSceneName}场景`);
    }

    // 6. 检查置信度
    const confidence = data.detections.confidence || 0;
    if (confidence < 0.5) {
      throw new Error(`场景匹配度不足(当前:${(confidence*100).toFixed(1)}%)`);
    }

    console.log('[DEBUG] 场景验证通过，置信度:', confidence);

    return {
      success: true,
      sceneResult: {
        ...data,
        displayScene: cnSceneName, // 存储中文场景名
        confidence: confidence
      },
      objectResult: null
    };

  } catch (error) {
    console.error('[SCENE_VERIFY_ERROR]', error);
    throw new Error(`场景验证失败: ${error.message}`);
  }
},

// 物体类型验证
async verifyObjectRequirement(imagePath, objectName) {
  try {
    const res = await new Promise((resolve, reject) => {
      wx.uploadFile({
        url: `https://${apiDomain}/flask/api/object/recognition`,
        filePath: imagePath,
        name: 'image',
        header: { 
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'multipart/form-data'
        },
        formData: {
          target_object: objectName
        },
        success: resolve,
        fail: reject
      });
    });

    const data = JSON.parse(res.data);
    if (data.code !== "0" && data.code !== "200") {
      throw new Error(data.message || '物体识别失败');
    }
    
    // 检查是否包含目标物体
    const containsTarget = data.objects.some(
      obj => obj.name === objectName && obj.confidence > 0.7
    );
    
    if (!containsTarget) {
      throw new Error(`未检测到${objectName}`);
    }
    
    return {
      success: true,
      sceneResult: null,
      objectResult: data
    };
  } catch (error) {
    throw new Error(`物体验证失败: ${error.message}`);
  }
},

// 检查地标是否有效
checkLandmarkValid(sceneRes, objectRes) {
  const { landmark_name } = this.data.challenge;
  
  // 简单示例：检查场景是否匹配
  if (landmark_name === '故宫') {
    return sceneRes.scene === 'buildings' && 
           objectRes.objects.some(obj => obj.includes('ancient'));
  }
  
  return true;
},

  // 验证位置
  async checkLocation() {
    console.groupCollapsed('====== 位置验证流程开始 ======');
    try {
      // 1. 检查当前存储的位置数据
      console.log('[1] 当前userLocation:', this.data.userLocation);
      
      // 2. 获取最新位置
      if (!this.data.userLocation) {
        console.warn('[2] 未获取位置，开始获取...');
        const { latitude, longitude } = await this.getUserLocation();
        this.setData({ 
          userLocation: { lat: latitude, lng: longitude }
        });
        console.log('[2] 获取到的新位置:', { latitude, longitude });
      }

      // 3. 打印挑战信息
      console.log('[3] 当前挑战数据:', {
        id: this.data.id,
        challengeLocation: this.data.challengeLocation,
        radius: this.data.challenge?.radius
      });

      // 4. 提交验证
      console.log('[4] 开始提交验证...');
      const res = await this.submitLocationVerification(
        this.data.userLocation.lat,
        this.data.userLocation.lng
      );
      
      // 5. 处理结果
      console.log('[5] 验证结果:', res);
      this.setData({ 
        locationVerified: res.data,
        locationResult: res.data
      });
      console.log(this.data.locationResult, this.data.locationVerified)
      if(this.data.locationVerified){
        this.watchDataChange();
      }
      wx.showToast({ 
        title: `验证${res.data ? '成功' : '失败'}`,
        icon: res.code === "0" ? 'success' : 'none'
      });

    } catch (error) {
      console.error('[ERROR] 验证流程异常:', error);
      wx.showToast({ 
        title: error.message || '验证异常', 
        icon: 'none',
        duration: 3000
      });
    } finally {
      console.groupEnd();
    }
  },

  // 获取用户位置
  async getUserLocation() {
    try {
      const { authSetting } = await new Promise(resolve => {
        wx.getSetting({
          success: resolve,
          fail: () => resolve({ authSetting: {} })
        });
      });
  
      if (authSetting['scope.userLocation'] === undefined) {
        // 首次申请权限
        await new Promise((resolve, reject) => {
          wx.authorize({
            scope: 'scope.userLocation',
            success: resolve,
            fail: () => reject(new Error('用户拒绝了位置权限'))
          });
        });
      } else if (authSetting['scope.userLocation'] === false) {
        // 已拒绝，需要引导设置
        await new Promise((resolve, reject) => {
          wx.showModal({
            title: '需要位置信息权限',
            content: '请在设置中授权位置信息',
            success(res) {
              if (res.confirm) {
                wx.openSetting({
                  success(settingData) {
                    if (settingData.authSetting['scope.userLocation']) {
                      resolve();
                    } else {
                      reject(new Error('未授权位置权限'));
                    }
                  },
                  fail: reject
                });
              } else {
                reject(new Error('用户取消了授权设置'));
              }
            }
          });
        });
      }
  
      // 已授权，获取位置信息
      const location = await new Promise((resolve, reject) => {
        wx.getLocation({
          type: 'gcj02',
          success: resolve,
          fail: () => reject(new Error('获取位置失败，请检查GPS是否开启'))
        });
      });
  
      return location;
    } catch (error) {
      console.error('位置获取失败:', error);
      throw error;
    }
  }, 

 // 人脸验证
  async verifyFace(){
    if (!this.data.challenge.need_face_verify) return;

    try {
      wx.showLoading({ title: '准备人脸验证...', mask: true });
      
      const isRegistered = await this.checkFaceRegistered();
      if (isRegistered === "-1") {
        wx.hideLoading();
        wx.showModal({
          title: '提示',
          content: '请先在个人资料页面上传人脸图片',
          showCancel: false,
          success: () => {
            wx.navigateTo({ url: '/pages/face/register' });
          }
        });
        return;
      }
      
      let randomNum;
      do {
        randomNum = Math.floor(Math.random() * 6) + 1;
      } while (randomNum === 3);
      
      wx.hideLoading();
      
      // 显示摄像头（人脸模式）
      this.showCameraView('face', 'front');
      
      this.setData({ 
        showFaceVerify: true,
        randomGestureNumber: randomNum
      }, () => {
        setTimeout(() => {
          this.startFaceDetection();
        }, 500);
      });
      
    } catch (error) {
      console.error('[FACE_INIT_ERROR]', error);
      wx.hideLoading();
      wx.showToast({ 
        title: '初始化人脸验证失败', 
        icon: 'none',
        duration: 3000
      });
    }
  },

// 开始人脸检测
startFaceDetection() {
  // 清除之前的定时器
  if (this.data.faceDetectionInterval) {
    clearInterval(this.data.faceDetectionInterval);
  }
  
  let detectionCount = 0;
  const maxDetectionCount = 15; // 最多尝试15次
  
  this.setData({ isFaceDetecting: true });
  
  this.data.faceDetectionInterval = setInterval(async () => {
    if (!this.data.isFaceDetecting || detectionCount >= maxDetectionCount) {
      this.stopFaceDetection();
      if (detectionCount >= maxDetectionCount) {
        wx.showToast({
          title: '人脸验证超时，请重试',
          icon: 'none',
          duration: 3000
        });
      }
      return;
    }
    
    detectionCount++;
    
    try {
      // 1. 获取摄像头帧
      const frameRes = await new Promise((resolve, reject) => {
        this.data.cameraContext.takePhoto({
          quality: 'high',
          success: resolve,
          fail: reject
        });
      });
      
      // 2. 验证人脸
      const faceRes = await this.verifyFaceWithAPI(frameRes.tempImagePath);
      console.log('人脸检测结果:', faceRes);
      
      if (faceRes.code === "0" && faceRes.match) {
        // 人脸验证通过（仅设置临时状态）
        this.stopFaceDetection();
        this.setData({ 
          faceImage: frameRes.tempImagePath,
          faceVerifiedOnly: true, // 仅表示人脸验证通过
          faceVerifyConfidence: faceRes.confidence
        });
        
        wx.showToast({ 
          title: `人脸验证通过(相似度:${(faceRes.confidence*100).toFixed(1)}%)`, 
          icon: 'none',
          duration: 3000
        });
        
        // 自动开始手势验证
        this.startGestureVerification();
      } else if (faceRes.code === "0" && !faceRes.match) {
        // 人脸不匹配
        console.log('人脸不匹配，继续检测...');
      } else {
        throw new Error(faceRes.message || '人脸验证失败');
      }
    } catch (error) {
      console.error('[FACE_DETECTION_ERROR]', error);
      if (detectionCount >= maxDetectionCount) {
        wx.showToast({
          title: error.message || '人脸验证失败',
          icon: 'none',
          duration: 3000
        });
      }
    }
  }, 1500); // 每1.5秒检测一次
},

// 调用人脸验证API
async verifyFaceWithAPI(imagePath) {
  try {
    const res = await new Promise((resolve, reject) => {
      wx.uploadFile({
        url: `https://${apiDomain}/flask/api/face/verify`,
        filePath: imagePath,
        name: 'image',
        header: { 
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'multipart/form-data'
        },
        success: resolve,
        fail: reject
      });
    });

    const data = JSON.parse(res.data);
    return {
      code: data.code,
      match: data.match,
      confidence: data.confidence,
      message: data.message,
      userId: data.user_id
    };
  } catch (error) {
    console.error('[FACE_API_ERROR]', error);
    throw new Error('人脸验证服务异常');
  }
},

// 停止人脸检测
stopFaceDetection() {
  clearInterval(this.data.faceDetectionInterval);
  this.setData({ 
    isFaceDetecting: false,
    faceDetectionInterval: null
  });
},

// 检查人脸是否注册
checkFaceRegistered() {
  return new Promise((resolve) => {
    wx.request({
      url: `https://${apiDomain}/flask/api/face/check_registered`,
      method: 'POST',
      header: { 'Authorization': `Bearer ${wx.getStorageSync('token')}` },
      success: (res) => resolve(res.data.code),
      fail: () => resolve(false)
    });
  });
},

// 关闭人脸验证
closeFaceVerify() {
  this.stopFaceDetection();
  this.setData({ 
    showFaceVerify: false,
    faceVerifiedOnly: false
  });
},


  async captureFace() {
    const ctx = wx.createCameraContext();
    
    try {
      // 1. 拍摄照片
      const res = await new Promise((resolve, reject) => {
        ctx.takePhoto({
          quality: 'high',
          success: resolve,
          fail: reject
        });
      });
      
      // 2. 验证人脸
      const faceRes = await this.verifyWithAI('face', res.tempImagePath);
      console.log('人脸验证结果:', faceRes);
      
      if (!faceRes.verified) {
        throw new Error('人脸验证未通过');
      }
      
      // 3. 上传照片
      wx.showLoading({ title: '上传中...' });
      const uploadRes = await wx.uploadFile({
        url: `https://${apiDomain}/flask/api/face/verify`,
        filePath: res.tempImagePath,
        name: 'image',
        header: { 'Authorization': `Bearer ${wx.getStorageSync('token')}` }
      });
      
      const uploadData = JSON.parse(uploadRes.data);
      if (uploadData.code === "200") {
        this.setData({
          faceImage: uploadData.data.image_url,
          isFaceVerified: true,
          showFaceVerify: false,
          faceResult: faceRes
        });
        wx.showToast({ title: '人脸验证通过', icon: 'success' });
      } else {
        throw new Error(uploadData.msg || '上传失败');
      }
    } catch (error) {
      console.error('[FACE_ERROR]', error);
      wx.showToast({ 
        title: error.message || '人脸验证失败', 
        icon: 'none',
        duration: 3000
      });
    } finally {
      wx.hideLoading();
    }
  },


// 开始手势验证
  startGestureVerification() {
    this.stopFaceDetection();

    // 显示摄像头（手势模式）
    this.showCameraView('gesture', 'front');
    
    this.setData({
      showFaceVerify: false,
      showGestureVerify: true,
      gestureDetectionInterval: null,
      isGestureDetecting: false
    }, () => {
      wx.showToast({ 
        title: `请展示数字 ${this.data.randomGestureNumber}`, 
        icon: 'none',
        duration: 1500
      });
      setTimeout(() => {
        this.startGestureDetection();
      }, 500);
    });
  },

  // 关闭所有摄像头相关操作
  closeAllCameraOperations() {
    this.stopFaceDetection();
    this.stopGestureDetection();
    this.hideCameraView();
    this.setData({
      showFaceVerify: false,
      showGestureVerify: false
    });
  },
// 开始手势检测
startGestureDetection() {
  // 清除之前的定时器
  if (this.data.gestureDetectionInterval) {
    clearInterval(this.data.gestureDetectionInterval);
  }
  
  // 确保有有效的摄像头上下文
  if (!this.data.cameraContext) {
    this.setData({
      cameraContext: wx.createCameraContext()
    });
  }

  let detectionCount = 0;
  const maxDetectionCount = 20; // 最多尝试20次
  
  this.setData({ 
    isGestureDetecting: true
  });
  
  this.data.gestureDetectionInterval = setInterval(async () => {
    if (!this.data.isGestureDetecting || detectionCount >= maxDetectionCount) {
      this.stopGestureDetection();
      if (detectionCount >= maxDetectionCount) {
        wx.showToast({
          title: '手势验证超时，请重试',
          icon: 'none',
          duration: 3000
        });
      }
      return;
    }
    
    detectionCount++;
    
    try {
      // 1. 获取摄像头帧
      const frameRes = await new Promise((resolve, reject) => {
        this.data.cameraContext.takePhoto({
          quality: 'high',
          success: resolve,
          fail: (err) => {
            console.error('获取摄像头帧失败:', err);
            // 重新初始化摄像头
            this.setData({ cameraContext: wx.createCameraContext() });
            reject(err);
          }
        });
      });
      
      // 2. 验证手势数字
      const gestureRes = await this.verifyGestureNumber(frameRes.tempImagePath);
      console.log('手势检测结果:', gestureRes);
      
      if (gestureRes.code === 0 && gestureRes.found) {
        // 检查手势数字是否正确
        if (gestureRes.detections.gesture == this.data.randomGestureNumber) {
          // 手势验证通过
          this.stopGestureDetection();
          this.setData({ 
            gestureVerifyImage: frameRes.tempImagePath,
            gestureVerifyResult: gestureRes,
            gestureVerified: true, // 手势验证通过
            showGestureVerify: false
          });
           // 双重验证通过
          if (this.data.faceVerifiedOnly && this.data.gestureVerified) {
            this.setData({
              isFaceVerified: true // 最终验证状态
            });
            this.watchDataChange();
          }
          wx.showToast({ 
            title: `手势验证通过(数字${gestureRes.detections.gesture}, 置信度:${(gestureRes.detections.confidence*100).toFixed(1)}%)`, 
            icon: 'success',
            duration: 3000
          });
        } else {
          console.log(`检测到数字${gestureRes.detections.gesture}, 需要数字${this.data.randomGestureNumber}`);
          // 手势检测不成功时重新初始化摄像头
          this.setData({ cameraContext: wx.createCameraContext() });
        }
      } else {
        // 手势检测失败时重新初始化摄像头
        this.setData({ cameraContext: wx.createCameraContext() });
        throw new Error(gestureRes.message || '手势验证失败');
      }
    } catch (error) {
      console.error('[GESTURE_DETECTION_ERROR]', error);
      // 发生错误时重新初始化摄像头
      this.setData({ cameraContext: wx.createCameraContext() });
      
      if (detectionCount >= maxDetectionCount) {
        wx.showToast({
          title: error.message || '手势验证失败',
          icon: 'none',
          duration: 3000
        });
      }
    }
  }, 500); // 每0.5秒检测一次
},

// 停止手势检测
stopGestureDetection() {
  clearInterval(this.data.gestureDetectionInterval);
  this.setData({ 
    isGestureDetecting: false,
    gestureDetectionInterval: null
  });
},

// 调用手势验证API
async verifyGestureNumber(imagePath) {
  try {
    const res = await new Promise((resolve, reject) => {
      wx.uploadFile({
        url: `https://${apiDomain}/flask/api/gesture/number`,
        filePath: imagePath,
        name: 'image',
        header: { 
          'Authorization': `Bearer ${wx.getStorageSync('token')}`,
          'Content-Type': 'multipart/form-data'
        },
        success: resolve,
        fail: reject
      });
    });

    const data = JSON.parse(res.data);
    return {
      code: data.code,
      found: data.found,
      detections: data.detections || {},
      message: data.message
    };
  } catch (error) {
    console.error('[GESTURE_API_ERROR]', error);
    throw new Error('手势验证服务异常');
  }
},

// 关闭手势验证
closeGestureVerify() {
  this.stopGestureDetection();
  this.setData({ 
    showGestureVerify: false,
    gestureVerified: false // 重置状态
  });
},

  // 提交挑战
  async submitChallenge() {
    if (!this.validateSubmission()) return;
    
    wx.showLoading({ title: '提交中...' });
    
    try {
      // 调试输出evidence信息
      console.group('[DEBUG] 提交证据信息');
      console.log('证据数组:', this.data.evidence);
      this.data.evidence.forEach((item, index) => {
        console.log(`证据#${index + 1}:`, {
          type: item.type,
          id: item.id,
          url: item.url,
          uploadTime: item.uploadTime,
          ...(item.gestureType ? { gestureType: item.gestureType } : {})
        });
      });
      console.groupEnd();
      
      // 确保有用户位置
      if (!this.data.userLocation) {
        const { latitude, longitude } = await this.getUserLocation();
        this.setData({
          userLocation: { lat: latitude, lng: longitude }
        });
      }
  
      // 提交数据
      const res = await this.submitChallengeData(
        this.data.userLocation.lat,
        this.data.userLocation.lng
      );
      
      console.log('[DEBUG] 提交挑战API响应:', res);
      
      if (res.data.code === "0") {
        wx.showToast({ title: '提交成功', icon: 'success' });
        setTimeout(() => wx.navigateBack(), 1500);
      } else {
        throw new Error(res.data.msg || '提交失败');
      }
    } catch (error) {
      console.error('[SUBMIT_ERROR]', error);
      wx.showToast({ 
        title: error.message || '提交失败', 
        icon: 'none',
        duration: 3000
      });
    } finally {
      wx.hideLoading();
    }
  },
 
  // 在Page对象中添加统一的验证方法
  async verifyWithAI(type, imagePath) {
    const apiMap = {
      scene: '/api/scene/recognition',
      gesture: '/api/gesture/semantic',
      object: '/api/object/recognition',
      face: '/api/face/verify'
    };

    if (!apiMap[type]) {
      throw new Error('不支持的验证类型');
    }

    try {
      wx.showLoading({ title: '验证中...' });
      
      const res = await new Promise((resolve, reject) => {
        wx.uploadFile({
          url: `https://${apiDomain}${apiMap[type]}`,
          filePath: imagePath,
          name: 'image',
          header: { 
            'Authorization': `Bearer ${wx.getStorageSync('token')}`,
            'Content-Type': 'multipart/form-data'
          },
          success: resolve,
          fail: reject
        });
      });

      const data = JSON.parse(res.data);
      if (data.code !== "200" && data.code !== "0") {
        throw new Error(data.msg || `${type}验证失败`);
      }
      
      return data.data;
    } catch (error) {
      console.error(`[${type.toUpperCase()}_ERROR]`, error);
      throw error;
    } finally {
      wx.hideLoading();
    }
  },
  // 提交数据
  async submitChallengeData(latitude, longitude) {
    // 计算AI验证状态
    const { 
      challenge, 
      gestureVerified, 
      landmarkVerified, 
      isFaceVerified 
    } = this.data;
  
    const aiVerified = (!challenge.gesture_type || gestureVerified) &&
      (!challenge.specialRequirement || landmarkVerified) &&
      (!challenge.need_face_verify || isFaceVerified);
    
    console.log('提交的数据', {
      location: {
        lng: this.data.userLocation.lng,
        lat: this.data.userLocation.lat
      },
      file_url: JSON.stringify(this.data.evidence),
      ai_verified: aiVerified, // 添加AI验证状态
      verification_details: { // 添加详细验证状态
        gesture: challenge.gesture_type ? gestureVerified : null,
        special: challenge.specialRequirement ? landmarkVerified : null,
        face: challenge.need_face_verify ? isFaceVerified : null
      }
    })
    return new Promise((resolve, reject) => {
      wx.request({
        url: `https://${apiDomain}/api/challenges/${this.data.id}/submit`,
        method: 'POST',
        header: { 'Authorization': `Bearer ${wx.getStorageSync('token')}` },
        data: {
          location: {
            lng: this.data.userLocation.lng,
            lat: this.data.userLocation.lat
          },
          file_url: JSON.stringify(this.data.evidence),
          ai_verified: aiVerified, // 添加AI验证状态
          verification_details: { // 添加详细验证状态
            gesture: challenge.gesture_type ? gestureVerified : null,
            special: challenge.specialRequirement ? landmarkVerified : null,
            face: challenge.need_face_verify ? isFaceVerified : null
          }
        },
        success: (res) => {
          if (res.statusCode === 200) {
            resolve(res);
          } else {
            reject(new Error(`HTTP ${res.statusCode}: ${res.data.msg || '提交失败'}`));
          }
        },
        fail: (err) => {
          reject(new Error(`网络错误: ${err.errMsg}`));
        }
      });
    });
  },

  // 验证提交数据
  validateSubmission() {
    const errors = [];
    
    // 手势验证改为可选，只要有上传图片即可
    if (this.data.challenge.gesture_type && !this.data.gestureImage) {
      errors.push('请上传手势照片');
    }
    
    // 特殊打卡验证改为可选，只要有上传图片即可
    if (this.data.challenge.specialRequirement && !this.data.specialImage) {
      errors.push('请上传特殊打卡照片');
    }
    
    if (!this.data.locationVerified) {
      errors.push('请先验证位置');
    }
    
    if (this.data.challenge.need_face_verify && !this.data.isFaceVerified) {
      errors.push('请完成双重验证');
    }
    
    if (errors.length > 0) {
      wx.showToast({ 
        title: errors.join('，'), 
        icon: 'none',
        duration: 3000
      });
      return false;
    }
    
    return true;
  },

  
  // 格式化时间
  formatTime(timeStr) {
    if (!timeStr) return '';
    const date = new Date(timeStr);
    return `${date.getFullYear()}-${date.getMonth()+1}-${date.getDate()}`;
  },

  // 更新剩余时间
  updateRemainTime() {
    if (!this.data.challenge?.end_time) return;
    
    const endDate = new Date(this.data.challenge.end_time);
    const now = new Date();
    const diffTime = endDate - now;
    
    if (diffTime <= 0) {
      this.setData({ remainTimeText: '已结束' });
      return;
    }
    
    const diffDays = Math.floor(diffTime / (1000 * 60 * 60 * 24));
    this.setData({ remainTimeText: diffDays > 0 ? `${diffDays}天后截止` : '今天截止' });
  },
  // 图片加载成功回调
  handleImageLoad(e) {
    console.log('图片加载成功:', e.detail);
    const { index } = e.currentTarget.dataset;
    this.setData({
      [`challenge.images[${index}].loaded`]: true
    });
  },
  
  // 图片加载失败回调
  handleImageError(e) {
    console.error('图片加载失败:', e.detail);
    const { index } = e.currentTarget.dataset;
    this.setData({
      [`challenge.images[${index}].error`]: true
    });
    
    // 尝试使用原始URL
    setTimeout(() => {
      this.setData({
        [`challenge.images[${index}].url`]: this.data.challenge.images[index].originalUrl
      });
    }, 1000);
  }
  
});