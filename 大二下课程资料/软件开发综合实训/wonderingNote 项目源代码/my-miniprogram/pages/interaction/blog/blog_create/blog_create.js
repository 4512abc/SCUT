import { apiDomain } from "../../../../config";

const request = (options) => {
  return new Promise((resolve, reject) => {
    const token = wx.getStorageSync('token');
    wx.request({
      ...options,
      header: {
        'Content-Type': 'application/json',
        'Authorization': token,
        ...options.header
      },
      success: (res) => {
        if (res.statusCode === 200) {
          resolve(res.data);
        } else {
          reject(res);
        }
      },
      fail: reject
    });
  });
};

const uploadFile = (options) => {
  return new Promise((resolve, reject) => {
    const token = wx.getStorageSync('token');
    wx.uploadFile({
      ...options,
      header: {
        'Authorization': token ? `Bearer ${token}` : '',
        ...options.header
      },
      success: (res) => {
        if (res.statusCode === 200) {
          resolve(JSON.parse(res.data));
        } else {
          reject(res);
        }
      },
      fail: reject
    });
  });
};

Page({
  data: {
    title: '',
    mood: '',
    weather: '',
    visibility: 'public',
    content: '',
    wordCount: 0,
    showMoodPicker: false,
    showWeatherPicker: false,
    showTagPicker: false,
    tags: [],
    selectedTags: [],
    selectedTagsText: '',
    location: [116.403850, 39.913790],
    newTag: '',
    landmark_name: '请选择位置',
    mediaType: '', // 'image' 或 'video'
    mediaList: [], // 图片列表或视频路径
    moodList: [
      { value: 'happy', label: '开心' },
      { value: 'calm', label: '平静' },
      { value: 'excited', label: '兴奋' },
      { value: 'sad', label: '难过' },
      { value: 'angry', label: '愤怒' },
      { value: 'anxious', label: '焦虑' },
      { value: 'relaxed', label: '放松' },
      { value: 'grateful', label: '感恩' }
    ],
    weatherList: [
      { value: 'sunny', label: '晴天' },
      { value: 'cloudy', label: '多云' },
      { value: 'rain', label: '小雨' },
      { value: 'storm', label: '暴雨' },
      { value: 'snow', label: '雪天' },
      { value: 'fog', label: '雾霾' },
      { value: 'windy', label: '大风' },
      { value: 'hail', label: '冰雹' }
    ],
    // 图标映射配置
    moodIcons: {
      '开心': '/assets/icons/mood/happy.jpg',
      '平静': '/assets/icons/mood/calm.jpg',
      '兴奋': '/assets/icons/mood/excited.jpg',
      '难过': '/assets/icons/mood/sad.jpg',
      '愤怒': '/assets/icons/mood/angry.jpg',
      '焦虑': '/assets/icons/mood/anxious.jpg',
      '放松': '/assets/icons/mood/relaxed.jpg',
      '感恩': '/assets/icons/mood/grateful.jpg'
    },
    weatherIcons: {
      '晴天': '/assets/icons/weather/sunny.jpg',
      '多云': '/assets/icons/weather/cloudy.jpg',
      '小雨': '/assets/icons/weather/rain.jpg',
      '暴雨': '/assets/icons/weather/storm.jpg',
      '雪天': '/assets/icons/weather/snow.jpg',
      '雾霾': '/assets/icons/weather/fog.jpg',
      '大风': '/assets/icons/weather/windy.jpg',
      '冰雹': '/assets/icons/weather/hail.jpg'
    },
    isDraft: false,
    draftKey: 'blog_draft_' + new Date().getFullYear(),  // 按年份存储草稿
    currentDate: '',
    lunarDate: '',
    tempVideoPath: ''
  },

  onLoad() {
    this.loadUserTags();
    this.setCurrentDate();
    this.loadDraft();

    const savedTheme = wx.getStorageSync('theme') || 0;
    this.setTheme(savedTheme);

  },

  setCurrentDate() {
    const now = new Date();
    const year = now.getFullYear();
    const month = (now.getMonth() + 1).toString().padStart(2, '0');
    const day = now.getDate().toString().padStart(2, '0');
    const hours = now.getHours().toString().padStart(2, '0');
    const minutes = now.getMinutes().toString().padStart(2, '0');
    
    // 简单模拟农历，实际应该调用农历计算接口
    const weekDays = ['周日', '周一', '周二', '周三', '周四', '周五', '周六'];
    const lunarMonths = ['正月', '二月', '三月', '四月', '五月', '六月', '七月', '八月', '九月', '十月', '冬月', '腊月'];
    const lunarDays = ['初一', '初二', '初三', '初四', '初五', '初六', '初七', '初八', '初九', '初十',
                      '十一', '十二', '十三', '十四', '十五', '十六', '十七', '十八', '十九', '二十',
                      '廿一', '廿二', '廿三', '廿四', '廿五', '廿六', '廿七', '廿八', '廿九', '三十'];
    
    this.setData({
      currentDate: `${year}-${month}-${day} ${hours}:${minutes}`,
      lunarDate: `${weekDays[now.getDay()]} ${lunarMonths[now.getMonth()]}${lunarDays[now.getDate() % 30]}`
    });
  },
  
  async loadUserTags() {
    try {
      const res = await request({
        url: '/api/user/tags',
        method: 'GET'
      });
      
      if (res.code === "0") {
        this.setData({ tags: res.data });
      }
    } catch (error) {
      console.error('加载标签失败:', error);
    }
  },
  
  onTitleChange(e) {
    this.setData({
      title: e.detail
    });
  },

  showMoodPicker() {
    this.setData({ showMoodPicker: true });
  },

  onCloseMoodPicker() {
    this.setData({ showMoodPicker: false });
  },

  selectMood(e) {
    const { value } = e.currentTarget.dataset;
    const selected = this.data.moodList.find(item => item.value === value)?.label;
    this.setData({
      mood: selected || '',
      showMoodPicker: false
    });
  },

  showWeatherPicker() {
    this.setData({ showWeatherPicker: true });
  },

  onCloseWeatherPicker() {
    this.setData({ showWeatherPicker: false });
  },
  
  selectWeather(e) {
    const { value } = e.currentTarget.dataset;
    const selected = this.data.weatherList.find(item => item.value === value)?.label;
    this.setData({
      weather: selected || '',
      showWeatherPicker: false
    });
  },

  showTagPicker() {
    this.setData({ showTagPicker: true });
  },

  onCloseTagPicker() {
    const selectedTagsText = this.data.selectedTags.length ?
      this.data.selectedTags.map(t => '#' + t).join(' ') : '';

    this.setData({
      showTagPicker: false,
      selectedTagsText
    });
  },

  onTagInput(e) {
    this.setData({ newTag: e.detail });
  },

  addNewTag() {
    const newTag = this.data.newTag.trim();
    if (!newTag) return;

    if (this.data.tags.includes(newTag)) {
      wx.showToast({
        title: '标签已存在',
        icon: 'none'
      });
      return;
    }

    const tags = [...this.data.tags, newTag];
    this.setData({
      tags,
      newTag: ''
    });
  },

  onTagSelect(e) {
    const tag = e.currentTarget.dataset.tag;
    const selectedTags = [...this.data.selectedTags];
    const index = selectedTags.indexOf(tag);

    if (index > -1) {
      selectedTags.splice(index, 1);
    } else {
      if (selectedTags.length >= 5) {
        wx.showToast({
          title: '最多选择5个标签',
          icon: 'none'
        });
        return;
      }
      selectedTags.push(tag);
    }

    const selectedTagsText = selectedTags.length ?
      selectedTags.map(t => '#' + t).join(' ') : '';

    this.setData({
      selectedTags,
      selectedTagsText
    });
  },

  onVisibilityChange(e) {
    this.setData({
      visibility: e.detail
    });
  },

  chooseLocation() {
    wx.chooseLocation({
      success: (res) => {
        this.setData({
          landmark_name: res.name,
          location: [res.longitude, res.latitude] // 保存经纬度数组，顺序是维度，经度
        });
      },
      fail: () => {
        wx.showToast({
          title: '请授权位置权限',
          icon: 'none'
        });
      }
    });
  },

  onContentChange(e) {
    const content = e.detail.value;
    const wordCount = content.length;

    if (wordCount > 1000) {
      wx.showToast({
        title: '内容最多1000字',
        icon: 'none'
      });
      return;
    }

    this.setData({
      content,
      wordCount
    });
  },

  chooseMedia() {
    wx.showActionSheet({
      itemList: ['上传图片（最多9张）', '上传视频（最大1分钟）'],
      success: (res) => {
        if (this.data.mediaList.length > 0) {
          const currentType = this.data.mediaType;
          const wantToUpload = res.tapIndex === 0 ? 'image' : 'video';
          if (currentType !== wantToUpload) {
            wx.showModal({
              title: '提示',
              content: '只能选择一种媒体类型，是否清除当前已选内容？',
              success: (result) => {
                if (result.confirm) {
                  this.setData({
                    mediaList: [],
                    mediaType: ''
                  }, () => {
                    this.uploadMedia(res.tapIndex);
                  });
                }
              }
            });
            return;
          }
        }
        this.uploadMedia(res.tapIndex);
      }
    });
  },

  uploadMedia(type) {
    if (type === 0) {
      // 图片逻辑（不变）
      const count = 9 - this.data.mediaList.length;
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
          const mediaList = [...this.data.mediaList, ...res.tempFilePaths];
          this.setData({
            mediaType: 'image',
            mediaList
          });
        }
      });
    } else {
      // 视频上传逻辑（增加来源选项 + 长视频限制）
      wx.showActionSheet({
        itemList: ['从相册/相机选择（≤60秒）', '从聊天文件选择（≤5分钟）'],
        success: (res) => {
          if (res.tapIndex === 0) {
            // 短视频
            wx.chooseVideo({
              sourceType: ['album', 'camera'],
              maxDuration: 60,
              camera: 'back',
              success: (res) => {
                this.setData({
                  mediaType: 'video',
                  mediaList: [res.tempFilePath]
                });
              }
            });
          } else if (res.tapIndex === 1) {
            // 长视频（聊天文件） + 检查时长
            wx.chooseMessageFile({
              count: 1,
              type: 'video',
              success: (res) => {
                wx.showLoading({ title: '处理中...' });
                // 设置 video 路径，触发 loadedmetadata
                this.setData({
                  mediaType: 'video',
                  mediaList: [res.tempFiles[0].path]
                });
                wx.hideLoading();
              }
            });
          }
        }
      });
    }
  },
  
  // 当视频加载完元数据时，检查时长是否超 5 分钟
  onLoadedMetadata(e) {
    const duration = e.detail.duration;
    if (duration > 300) {
      wx.showToast({
        title: '视频不能超过5分钟',
        icon: 'none'
      });
      this.setData({ tempVideoPath: '' });
      return;
    }
    // 合法，加入 mediaList
    this.setData({
      mediaType: 'video',
      mediaList: [this.data.tempVideoPath],
      tempVideoPath: ''
    });
  },  
  

  previewMedia(e) {
    const { url } = e.currentTarget.dataset;
    if (this.data.mediaType === 'image') {
      wx.previewImage({
        current: url,
        urls: this.data.mediaList
      });
    } else if (this.data.mediaType === 'video') {
      wx.previewMedia({
        sources: [{
          url: url,
          type: 'video'
        }]
      });
    }
  },

  deleteMedia(e) {
    const { index } = e.currentTarget.dataset;
    const mediaList = [...this.data.mediaList];
    mediaList.splice(index, 1);
    this.setData({
      mediaList,
      mediaType: mediaList.length === 0 ? '' : this.data.mediaType
    });
  },
  
  async uploadMediaFiles() {
    const mediaFilesId = [];
    console.log('[调试] 开始上传媒体文件，数量:', this.data.mediaList.length);
    
    for (let i = 0; i < this.data.mediaList.length; i++) {
      const filePath = this.data.mediaList[i];
      console.log('[调试] 正在上传第', i+1, '个文件:', filePath);
      
      try {
        const token = wx.getStorageSync('token');
        const res = await new Promise((resolve, reject) => {
          wx.uploadFile({
            url: 'https://' + apiDomain + '/api/files/upload',
            filePath: filePath,
            name: 'file',
            header: {
              'Authorization': token
            },
            success: (uploadRes) => {
              console.log('[调试] 文件上传原始响应:', uploadRes);
              try {
                const result = JSON.parse(uploadRes.data);
                console.log('[调试] 解析后的响应数据:', result);
                if (uploadRes.statusCode === 200 && (result.code === '200' || result.code === '0')) {
                  resolve(result);
                } else {
                  reject(result);
                }
              } catch (e) {
                console.log('[调试] JSON解析失败:', e);
                reject(e);
              }
            },
            fail: (error) => {
              console.log('[调试] 文件上传请求失败:', error);
              reject(error);
            }
          });
        });

        console.log('[调试] 上传结果:', res);
        if (res.data && res.data.file_url) {
          // 处理转义的双引号问题
          const unescapedJson = res.data.file_url.replace(/\\"/g, '"');
          console.log('[调试] 处理转义后的JSON字符串:', unescapedJson);
          
          try {
            const fileInfo = JSON.parse(unescapedJson);
            console.log('[调试] 解析后的文件信息:', fileInfo);
            
            if (fileInfo && fileInfo.id) {
              mediaFilesId.push(fileInfo.id);
              console.log('[调试] 已收集的文件ID:', mediaFilesId);
            } else {
              console.log('[调试] 文件信息缺少id字段:', fileInfo);
              throw new Error('文件信息缺少id字段');
            }
          } catch (e) {
            console.error('[调试] 解析file_url失败:', e);
            throw new Error('解析文件信息失败: ' + e.message);
          }
        } else {
          console.log('[调试] 响应数据缺少file_url字段:', res);
          throw new Error('响应数据缺少file_url字段');
        }
      } catch (error) {
        console.error('[调试] 文件上传捕获到错误:', error);
        throw new Error('文件上传失败: ' + error.message);
      }
    }
    console.log('[调试] 全部文件上传完成，返回ID列表:', mediaFilesId);
    return mediaFilesId;
  },

  async saveBlog() {
    console.log('[调试] 开始保存博文');
    
    if (!this.data.content) {
      wx.showToast({
        title: '请输入内容',
        icon: 'none'
      });
      return;
    }
  
    wx.showLoading({ title: '正在发布' });
    console.log('[调试] 显示加载中...');
    
    try {
      let mediaFilesId = [];
      if (this.data.mediaList.length > 0) {
        console.log('[调试] 准备上传媒体文件');
        console.log('[调试] 当前mediaList:', this.data.mediaList);
        console.log('[调试] 当前mediaType:', this.data.mediaType);
        mediaFilesId = await this.uploadMediaFiles();
        console.log('[调试] 媒体文件上传完成:', mediaFilesId);
      }
  
      let videos = [], images = [];
      if (this.data.mediaType === 'image') {
        console.log('[调试] 处理图片数据');
        images = mediaFilesId.map(id => ({
          id: id,
          url: `/api/files/${id}/download`
        }));
        console.log('[调试] 处理后的图片列表:', images);
      } else if (this.data.mediaType === 'video') {
        console.log('[调试] 处理视频数据');
        videos = mediaFilesId.map(id => ({
          id: id,
          url: `/api/files/${id}/download`
        }));
        console.log('[调试] 处理后的视频列表:', videos);
      }
      let blogData = null;
      if (this.data.mediaType === 'video') {
        blogData = {
          title: this.data.title || '无标题',
          content: this.data.content,
          images: '',
          videos: JSON.stringify(videos),
          location: this.data.location,
          is_public: this.data.visibility === 'public',
          landmark_name: this.data.landmark_name  === "请选择位置" ? "未知" : this.data.landmark_name
        };
      }else{
        blogData = {
          title: this.data.title || '无标题',
          content: this.data.content,
          images: JSON.stringify(images),
          videos: JSON.stringify(videos),
          location: this.data.location,
          is_public: this.data.visibility === 'public',
          landmark_name: this.data.landmark_name  === "请选择位置" ? "未知" : this.data.landmark_name
        };
      }
      console.log('[调试] 准备发送的完整博文数据:', JSON.stringify(blogData, null, 2));
  
      const token = wx.getStorageSync('token');
      console.log('[调试] 使用的token:', token);
  
      console.log('[调试] 开始发送请求...');
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: 'https://' + apiDomain + '/api/posts/create',
          method: 'POST',
          data: blogData,
          header: {
            'Content-Type': 'application/json',
            'Authorization': token
          },
          success: (res) => {
            console.log('[调试] 请求成功，状态码:', res.statusCode);
            console.log('[调试] 响应数据:', res.data);
            if (res.statusCode === 200 || res.code === "0") {
              resolve(res.data);
            } else {
              console.log('[调试] 请求失败，非200状态码');
              reject(new Error(`HTTP ${res.statusCode}: ${JSON.stringify(res.data)}`));
            }
          },
          fail: (error) => {
            console.log('[调试] 请求失败:', error);
            reject(error);
          }
        });
      });
  
      console.log('[调试] 请求完成，检查返回码:', res.code);
      if (res.code === "0") {
        console.log('[调试] 发布成功，准备清理草稿');
        wx.removeStorageSync(this.data.draftKey);
        wx.hideLoading();
        wx.showToast({
          title: '发布成功',
          icon: 'success',
          success: () => {
            console.log('[调试] 准备返回上一页');
            setTimeout(() => wx.navigateBack(), 1500);
          }
        });
      } else {
        console.log('[调试] 业务处理失败:', res);
        throw new Error('业务处理失败: ' + JSON.stringify(res));
      }
    } catch (error) {
      console.error('[调试] 捕获到错误:', error);
      wx.hideLoading();
      wx.showToast({
        title: '发布失败',
        icon: 'error'
      });
    }
  },

  loadDraft() {
    const draft = wx.getStorageSync(this.data.draftKey);
    if (draft) {
      wx.showModal({
        title: '提示',
        content: '检测到未发布的草稿,是否恢复?',
        success: (res) => {
          if (res.confirm) {
            this.setData({
              ...draft,
              isDraft: true
            });
          } else {
            wx.removeStorageSync(this.data.draftKey);
          }
        }
      });
    }
  },

  saveDraft() {
    const draft = {
      title: this.data.title,
      content: this.data.content,
      mood: this.data.mood,
      weather: this.data.weather,
      selectedTags: this.data.selectedTags,
      location: this.data.location,
      landmark_name: this.data.landmark_name,
      visibility: this.data.visibility,
      mediaType: this.data.mediaType,
      mediaList: this.data.mediaList
    };
    
    wx.setStorageSync(this.data.draftKey, draft);
    wx.showToast({
      title: '已保存草稿',
      icon: 'success'
    });
  },

  navigateBack() {
    if (this.data.content) {
      wx.showModal({
        title: '提示',
        content: '是否保存为草稿？',
        confirmText: '保存',
        cancelText: '不保存',
        success: (res) => {
          if (res.confirm) {
            this.saveDraft();
          }
          wx.navigateBack();
        }
      });
    } else {
      wx.navigateBack();
    }
  }
});