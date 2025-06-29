const { apiDomain } = require("../../../../config")

Page({
  data: {
    
    debugMode: true,
    // ========== 加载状态 ==========
    loading: true,      // 全局加载状态
    error: false,       // 是否加载出错
    loadingComments: false, // 评论加载状态
    submittingComment: false, // 评论提交状态

    // ========== 用户信息 ==========
    userInfo: {
      account: '',      // 用户账号 - 对应initial_info.user_account
      avatar: ''        // 用户头像 - 对应initial_info.user_avatar
    },

    // ========== 博文基础信息 ==========
    postInfo: {
      id: '',           // 博文ID - 对应post_list.id
      title: '',       // 标题 - 对应post_list.title
      cover: '',        // 封面图 - 对应post_list.cover
      viewCount: 0,     // 浏览数 - 对应post_list.view_count
      likeCount: 0,     // 点赞数 - 对应post_list.like_count
      commentCount: 0,   // 评论数 - 对应post_list.comment_count
      createTime: '',    // 创建时间 - 对应post_list.create_time
      lunarDate: '',
      landmark: '',       // 地标 - 对应post_list.landmark_name
      lat: '',
      lng: ''
    },

    // ========== 博文详情内容 ==========
    postDetail: {
      content: '',       // 正文内容 - 对应details.content
      images: [],       // 图片列表 - 对应details.images(需split)
      videos: []        // 视频列表 - 对应details.videos
    },

    // ========== 交互状态 ==========
    isLiked: "",     // 是否已点赞
    showCommentInput: false, // 是否显示评论输入框
    commentContent: '',  // 评论输入内容
    maxCommentLength: 1000, // 评论最大长度

    // ========== 评论相关 ==========
    comments: [], // 评论列表
    expandedComments: {}, // 记录哪些评论是展开的 {commentId: boolean}
    loadingSubComments: {}, // 记录正在加载的子评论 {commentId: boolean}
    subCommentsMap: {}, // 存储已加载的子评论 {parentId: [comment1, comment2]}
    page: 1,            // 评论当前页码
    pageSize: 10,       // 评论每页数量
    hasMore: true,      // 是否有更多评论
    nextCursor: '0',     // 下个游标页
    son_lastCursor: "0",

    // ========== 多媒体加载状态 ==========
    imageLoading: {}, // 记录每张图片的加载状态
    tempFilePaths: {}, // 存储临时文件路径
    // ========== 时间显示 ==========
    fullDate: '',        // 完整日期(根据createTime格式化)
    displayedDate: "", // 新增字段

    // 新增回复相关状态
    showReplyInput: false,
    replyingTo: '',       // 正在回复的用户名
    replyContent: '',     // 回复内容
    replyingCommentId: null, // 正在回复的评论ID

    currentSwiperIndex: 0, // 当前轮播图索引
    isDev: true // 开发环境标识

    // ========== 以下字段API未提供，如需保留需确认数据来源 ==========
    // mood: '',         // 心情状态
    // weather: '',      // 天气情况
    // tags: []          // 标签列表
    
  },
  
  onLoad(options) {
    if (!options.id || isNaN(parseInt(options.id))) {
      wx.showToast({ title: '参数错误', icon: 'none' })
      setTimeout(() => wx.navigateBack(), 1500)
      return
    }

    this.setData({ id: parseInt(options.id) })
    this.initData()
    this.updateTime()
    this.updateTimer = setInterval(() => this.updateTime(), 60000)
    
  },

  navigateToUserDetail(e){
    console.log(e)
    const userId = e.currentTarget.dataset.userid
    console.log('[准备跳转，用户id：]', userId)
    wx.navigateTo({
      url: `/pages/interaction/user_profile/user_profile?id=${userId}`,
    })
  },

  async initData() {
    this.setData({ loading: true });
    
    try {
      // 1. 先获取博文详情
      await this.fetchBlogDetail();
      
      // 2. 然后初始化点赞状态（依赖博文ID）
      await this.initLikeStatus();
      
      // 3. 最后获取评论
      await this.fetchComments();
      console.log("[初始化后的评论信息]", this.data.comments)
      this.setData({ loading: false });
    } catch (error) {
      console.error('初始化数据失败:', error);
      this.setData({ 
        loading: false,
        error: true
      });
      wx.showToast({ title: '加载失败', icon: 'none' });
    }
  },

  // 新增初始化点赞状态方法
  async initLikeStatus() {
    try {
      this.setData({ likeLoading: true });
      const token = wx.getStorageSync('token');
      const postId = this.data.id; // 使用正确的博文ID字段
  
      // 调试日志
      console.log('[initLikeStatus] 开始获取点赞状态', {
        postId: postId,
        token: token ? '存在' : '不存在'
      });
  
      // 调用获取点赞状态接口
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/v1/interactions/${postId}`,
          method: 'GET',
          header: {
            'Authorization': `Bearer ${token}`,
            'content-type': 'application/json'
          },
          success: (res) => {
            console.log('[initLikeStatus] 接口响应', res);
            resolve(res);
          },
          fail: reject
        });
      });
  
      // 处理接口返回数据
      if (res.statusCode !== 200) {
        throw new Error(res.data?.msg || '请求失败');
      }
  
      const isLiked = res.data?.data?.isLike || false;
      console.log('[initLikeStatus] 解析出的点赞状态', isLiked);
  
      this.setData({
        isLiked: isLiked ? "1" : "0",
        likeLoading: false
      });
  
    } catch (error) {
      console.error('[initLikeStatus] 初始化点赞状态失败:', error);
      this.setData({ 
        isLiked: "0", // 默认未点赞
        likeLoading: false 
      });
    }
  },

  // 修改后的点赞API调用方法
  callLikeApi(action = 'toggle') {
    console.log('[callLikeApi] 开始API调用，动作:', action);
    
    return new Promise((resolve, reject) => {
      const url = `https://${apiDomain}/api/v1/interactions/${this.data.id}`;
      console.log('[callLikeApi] 请求URL:', url);
      
      wx.request({
        url: url,
        method: 'POST',
        header: {
          'Authorization': `Bearer ${wx.getStorageSync('token')}`
        },
        success: (res) => {
          console.log('[callLikeApi] 请求成功，状态码:', res.statusCode);
          console.log('[callLikeApi] 响应头:', res.header);
          
          if (res.data.code !== '200' && res.data.code !== '0') {
            console.error('[callLikeApi] 业务逻辑错误:', res.data);
            reject(new Error(res.data.msg || '请求失败'));
            return;
          }
          
          console.log('[callLikeApi] 请求成功，返回数据:', res.data);
          resolve(res);
        },
        fail: (err) => {
          console.error('[callLikeApi] 请求失败:', err);
          reject(err);
        }
      });
    });
  },
  // 获取博文详情
  // 获取博文详情（修复版）
  async fetchBlogDetail() {
    console.group('获取博文详情');
    try {
      console.log('[1] 开始获取博文详情');
      this.setData({ loading: true });
      const token = wx.getStorageSync('token');
      
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/posts/${this.data.id}`,
          method: 'GET',
          header: { 'Authorization': `Bearer ${token}` },
          success: resolve,
          fail: reject
        });
      });
  
      console.log('[2] 原始API响应:', res.data);
  
      if (res.data.code !== '200' && res.data.code !== '0') {
        throw new Error(res.data.msg || '获取详情失败');
      }
  
      const apiData = res.data.data;
      console.log('[3] 完整API数据结构:', apiData);
  
      // 安全访问嵌套数据
      const postList = apiData.post_list || {};
      const details = apiData.details || {};
      const initialInfo = apiData.initial_info || {};
  
      // 初始化图片加载状态
      const imageLoading = {};
      const images = details.images ? 
        (Array.isArray(details.images) ? details.images : JSON.parse(details.images)) : 
        [];
      images.forEach((_, index) => {
        imageLoading[index] = true;
      });
  
      // 解析视频数据
      // 处理视频数据
      const videos = details.videos ? 
      (Array.isArray(details.videos) ? details.videos : JSON.parse(details.videos)) : 
      [];
      console.log('[4] 解析后的视频数据:', videos);

      // 下载视频
      const processedVideos = await Promise.all(
      videos.map(video => this.downloadVideo(video))
      );
      console.log('[5] 处理后的视频数据:', processedVideos);

      // 直接提取视频URL
      const videoUrls = processedVideos.map(video => video.url);
  
      // 设置基础信息（确保字段名正确）
      this.setData({
        userInfo: {
          account: initialInfo.user_account || '',
          avatar: initialInfo.user_avatar || ''
        },
        postInfo: {
          id: this.data.id,
          title: postList.title || '',
          cover: postList.cover || '',
          viewCount: postList.view_count || 0,
          likeCount: postList.like_count || 0,
          commentCount: postList.comment_count || 0,
          createTime: postList.create_time || '',
          landmark: postList.landmark_name || '',
          lat: postList.location.lat || '',
          lng: postList.location.lng || ''
        },
        postDetail:{
          content: details.content
        },
        loading: false,
        imageLoading
      });
  
      // 处理图片
      const processedImages = await Promise.all(
        images.map(img => this.downloadImage(img))
      );
      console.log('[处理后的图片数组]', processedImages)
  
      this.setData({
        'postDetail.images': processedImages,
        'parsedImages': processedImages.map(img => ({ id: img.id })),
        'imageCache': processedImages.reduce((cache, img) => {
          cache[img.id] = img.url;
          return cache;
        }, {}),
        'postDetail.videos': videoUrls,
        'videoCache': processedVideos.reduce((cache, video) => {
          cache[video.id] = video;
          return cache;
        }, {})
      });
  
      console.log('[6] 最终数据:', this.data);
  
    } catch (error) {
      console.error('获取详情失败:', error);
      this.setData({ 
        loading: false,
        error: true
      });
      wx.showToast({ title: '加载失败', icon: 'none' });
    } finally {
      console.groupEnd();
    }
  },
  
  // 添加视频下载方法
  async downloadVideo(video) {
    console.log('[下载视频] 开始下载视频:', video);
    try {
      const token = wx.getStorageSync('token');
      const res = await new Promise((resolve, reject) => {
        wx.downloadFile({
          url: `https://${apiDomain}${video.url}`,
          header: {
            'Authorization': `Bearer ${token}`
          },
          success: resolve,
          fail: reject
        });
      });
  
      console.log('[下载视频] 下载完成:', res);
      return {
        id: video.id,
        url: res.tempFilePath,
        originalUrl: video.url
      };
    } catch (error) {
      console.error('[下载视频] 下载失败:', error);
      return {
        id: video.id,
        url: null,
        originalUrl: video.url,
        error: true
      };
    }
  },

  getFileInfo: function(fileId) {
    return new Promise((resolve) => {
      const reqUrl = `https://${apiDomain}/api/files/${fileId}/download`;
      
      if (this.data.debugMode) {
        console.groupCollapsed(`[调试] 开始获取文件信息 ID:${fileId}`);
        console.log('请求URL:', reqUrl);
        console.log('时间戳:', new Date().toISOString());
      }

      wx.request({
        url: reqUrl,
        method: 'GET',
        responseType: 'arraybuffer',
        success: (res) => {
          if (this.data.debugMode) {
            console.log('[调试] 请求成功', {
              status: res.statusCode,
              headers: res.header,
              dataSize: res.data?.byteLength || 0,
              dataPreview: res.data ? new Uint8Array(res.data.slice(0, 4)) : null
            });
          }

          if (res.statusCode === 200 && res.data) {
            const tempFilePath = `${wx.env.USER_DATA_PATH}/${fileId}_${Date.now()}.jpg`;
            
            if (this.data.debugMode) {
              console.log('[调试] 准备写入临时文件:', tempFilePath);
            }

            wx.getFileSystemManager().writeFile({
              filePath: tempFilePath,
              data: res.data,
              encoding: 'binary',
              success: () => {
                if (this.data.debugMode) {
                  console.log('[调试] 文件写入成功', {
                    path: tempFilePath,
                    fileSize: res.data.byteLength
                  });
                  wx.getFileSystemManager().stat({
                    path: tempFilePath,
                    success: (stat) => console.log('[调试] 文件验证:', stat),
                    fail: (err) => console.error('[调试] 文件验证失败:', err)
                  });
                }
                resolve({ url: tempFilePath });
              },
              fail: (err) => {
                console.error('[调试] 文件写入失败:', err);
                resolve(null);
              }
            });
          } else {
            if (this.data.debugMode) {
              console.warn('[调试] 无效响应', res);
            }
            resolve(null);
          }
        },
        fail: (err) => {
          console.error('[调试] 请求失败:', err);
          resolve(null);
        },
        complete: () => {
          if (this.data.debugMode) {
            console.groupEnd();
          }
        }
      });
    });
  },

// 增强版downloadImage（带完整调试）
downloadImage: async function(fileInfo) {
  try {
    // 提取文件ID（保持原有逻辑）
    const fileId = typeof fileInfo === 'string' ? 
                 (fileInfo.match(/\d+/)?.[0] || fileInfo) : 
                 (fileInfo.id || fileInfo.url?.match(/\/(\d+)\//)?.[1]);

    // 直接下载文件
    const { tempFilePath } = await new Promise((resolve, reject) => {
      wx.downloadFile({
        url: `https://${apiDomain}/api/files/${fileId}/download`,
        success: (res) => res.statusCode === 200 ? resolve(res) : reject(res),
        fail: reject
      });
    });

    // 返回统一格式：{ id: 文件ID, url: 临时路径 }
    return {
      id: fileId,
      url: tempFilePath,
      isTemp: true // 标记为临时文件
    };

  } catch (error) {
    console.error('下载失败:', error);
    return {
      id: 'error',
      url: '/assets/images/image-error.jpg'
    };
  }
},

   // 点击回复按钮
   onTapReply(e) {
    const { commentId, userName } = e.currentTarget.dataset;
    console.log('点击回复按钮', commentId, userName); // 调试日志
    
    this.setData({
      showReplyInput: true,
      replyingTo: userName,
      replyingCommentId: commentId,
      replyContent: ''
    });
  },

   // 隐藏回复框
  hideReplyInput() {
    this.setData({
      showReplyInput: false,
      replyingTo: '',
      replyingCommentId: null
    });
  },

   // 回复输入处理
   onInputFocus(e) {
    console.log('输入框聚焦', e.detail);
  },

  onInputBlur(e) {
    console.log('输入框失焦', e.detail);
  },

  onReplyInput(e) {
    console.log('输入内容:', e.detail.value) // 添加调试日志
    const content = e.detail.value
    if (content.length <= this.data.maxCommentLength) {
      this.setData({
        replyContent: content
      });
    }else {
      // 超出字数限制时截取
      this.setData({
        replyContent: content.substring(0, this.data.maxCommentLength)
      })
      wx.showToast({
        title: `评论最多${this.data.maxCommentLength}字`,
        icon: 'none'
      })
    }
  },
  // 图片处理相关方法保持不变
  onImageLoad(e) {
    const { index } = e.currentTarget.dataset
    this.setData({
      [`imageLoading.${index}`]: false
    })
  },

  onImageError(e) {
    const { index } = e.currentTarget.dataset;
    const failedUrl = this.data.postDetail.images[index];
    
    console.error(`[图片加载失败] 索引: ${index}, URL: ${failedUrl}`);
    console.log('当前图片列表:', this.data.postDetail.images);
  
    this.setData({
      [`imageLoading.${index}`]: false,
      [`postDetail.images.${index}`]: '/images/image-error.jpg'
    });
  },
  
  onVideoError(e) {
    console.error('[视频加载错误] 详情:', e.detail);
    console.log('当前视频数据:', this.data.postDetail.videos);
    wx.showToast({
      title: '视频加载失败',
      icon: 'none'
    });
  },

  // 获取评论列表
  async fetchComments() {
    if (!this.data.hasMore || this.data.loadingComments) return;
    
    this.setData({ loadingComments: true });
    
    try {
      const token = wx.getStorageSync('token');
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/v1/comments/${this.data.id}`,
          method: 'GET',
          header: {
            'Authorization': `Bearer ${token}`
          },
          data: {
            size: this.data.pageSize,
            sort: 'id',
            lastCursor: this.data.page > 1 ? this.data.nextCursor : '0'
          },
          success: resolve,
          fail: reject
        });
      });

      if (res.data.code !== '0' && res.data.code !== '200') {
        throw new Error(res.data.msg || '获取评论失败');
      }

      const responseData = res.data.data;
      const newComments = responseData.data || [];
      console.log("[获取的评论信息原始响应]", responseData)
      console.log("[获取的评论信息原始数据]", newComments)
      
      const formattedComments = newComments.map(comment => {
        let avatar = '/static/images/default-avatar.jpg';
        if (comment.avater) {
          try {
            avatar = `https://${apiDomain}${JSON.parse(comment.avater).url}`;
          } catch (e) {
            console.warn("头像解析失败", e);
          }
        }
        let son_avatar = '/static/images/default-avatar.jpg';
        if (comment.son_avater) {
          try {
            son_avatar = `https://${apiDomain}${JSON.parse(comment.son_avater).url}`;
          } catch (e) {
            console.warn("头像解析失败", e);
          }
        }
        return {
          id: comment.id,
          userId: comment.user_id,
          userName: comment.account,
          userAvatar: avatar,
          content: comment.content,
          createTime: this.formatCommentTime(comment.create_time),
          hasMore: comment.is_have === true, // 或者 comment.is_have === "1"
          firstSubComment: comment.son_id ? {
            id: comment.son_id,
            userId: comment.son_userid,
            userName: comment.son_account,
            userAvatar: son_avatar,
            content: comment.son_content,
            createTime: this.formatCommentTime(comment.son_create_time)
          } : null
        };
      });
      
      console.log("[子评论]", formattedComments)
      this.setData({
        comments: this.data.page === 1 ? 
          formattedComments : 
          [...this.data.comments, ...formattedComments],
        hasMore: !!responseData.nextCursor,
        nextCursor: responseData.nextCursor,
        page: this.data.page + 1,
        loadingComments: false
      });

    } catch (error) {
      console.error('获取评论失败:', error);
      this.setData({ loadingComments: false });
      wx.showToast({ 
        title: error.message || '获取评论失败', 
        icon: 'none' 
      });
    }
  },

  // 获取全部子评论（增强调试版）
  async fetchAllSubComments(commentId) {
    console.groupCollapsed(`[调试] 开始获取子评论 commentId=${commentId}`);
    console.log('当前时间:', new Date().toISOString());
    console.log('当前评论状态:', {
      loadingSubComments: this.data.loadingSubComments[commentId],
      cachedCount: this.data.subCommentsMap[commentId]?.length || 0
    });
  
    if (this.data.loadingSubComments[commentId]) {
      console.warn('⚠️ 该评论正在加载中，跳过重复请求');
      console.groupEnd();
      return;
    }
  
    this.setData({
      [`loadingSubComments.${commentId}`]: true
    });
    console.log('✅ 设置loading状态为true');
  
    try {
      const token = wx.getStorageSync('token');
      
      // 构建查询参数
      const params = {
        root_id: commentId,
        size: 50,
        lastCursor: this.data.son_lastCursor,
        sort: "id"
      };
      
      // 构建查询字符串
      const queryString = Object.keys(params)
        .map(key => `${encodeURIComponent(key)}=${encodeURIComponent(params[key])}`)
        .join('&');
      
      const apiUrl = `https://${apiDomain}/api/v1/comments/much?${queryString}`;
      
      console.log('准备请求API:', {
        url: apiUrl,
        method: 'GET',
        params: params
      });
  
      const startTime = Date.now();
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: apiUrl,
          method: 'GET',
          header: { 'Authorization': `Bearer ${token}` },
          success: (res) => {
            console.log(`📡 请求成功 耗时:${Date.now() - startTime}ms`, {
              status: res.statusCode,
              dataSize: res.data?.data?.length || 0
            });
            resolve(res);
          },
          fail: (err) => {
            console.error('❌ 请求失败', err);
            reject(err);
          }
        });
      });
  
      console.log('原始API响应:', JSON.parse(JSON.stringify(res.data)));
  
      if (!res.data || (res.data.code !== '0' && res.data.code !== '200')) {
        const errMsg = res.data?.msg || '获取回复失败';
        console.error('API返回错误:', errMsg);
        throw new Error(errMsg);
      }
  
      const rawComments = res.data.data?.data || res.data.data || [];
      console.log('解析出的原始评论数据:', {
        count: rawComments.length,
        rawComments: rawComments
      });
  
      // 构建评论映射表
      const commentsMap = {};
      const childCommentsMap = {};
      
      rawComments.forEach((comment, index) => {
        const commentId = comment.id;
        const parentId = comment.parent_id || commentId;
  
        if (!commentId) {
          console.warn(`⚠️ 发现无效评论数据 index=${index}`, comment);
          return;
        }
        console.log('[单条评论信息]', comment)
        let avatar = '/static/images/default-avatar.jpg'
        if(comment.avater && comment.avater != '{}'){
          avatar = `https://${apiDomain}${JSON.parse(comment.avater).url}`
        }
        console.log('[处理后的头像url]', avatar)
        commentsMap[commentId] = {
          id: commentId,
          userId: comment.user_id,
          userName: comment.account,
          userAvatar: avatar,
          content: comment.content,
          createTime: this.formatCommentTime(comment.create_time),
          parentId: parentId,
          children: []
        };
        
        if (!childCommentsMap[parentId]) {
          childCommentsMap[parentId] = [];
        }
        childCommentsMap[parentId].push(commentId);
      });
  
      console.log('构建的评论映射表:', {
        commentsCount: Object.keys(commentsMap).length,
        childRelations: Object.keys(childCommentsMap).map(k => ({
          parentId: k,
          childrenCount: childCommentsMap[k].length
        }))
      });
  
      // 构建树形结构
      const buildCommentTree = (parentId) => {
        if (!childCommentsMap[parentId]) return [];
        
        return childCommentsMap[parentId].map(childId => {
          const comment = commentsMap[childId];
          return {
            ...comment,
            children: buildCommentTree(comment.id)
          };
        });
      };
  
      const subComments = buildCommentTree(commentId);
      console.log('构建的评论树:', {
        rootCount: subComments.length,
        sample: subComments[0] ? {
          id: subComments[0].id,
          childrenCount: subComments[0].children.length 
        } : null
      });
  
      // 扁平化处理
      const flattenComments = [];
      const flatten = (comments, level = 0) => {
        comments.forEach(comment => {
          flattenComments.push({
            ...comment,
            indentLevel: level,
            
            isSubComment: level > 0,
            parentUserName: commentsMap[comment.parentId]?.userName || null
          });
          flatten(comment.children, level + 1);
        });
      };
      flatten(subComments);
  
      console.log('扁平化后的评论列表:', {
        count: flattenComments.length,
        levels: [...new Set(flattenComments.map(c => c.indentLevel))],
        sample: flattenComments.slice(0, 3)
      });
  
      // 更新数据
      this.setData({
        [`subCommentsMap.${commentId}`]: flattenComments,
        [`loadingSubComments.${commentId}`]: false
      }, () => {
        console.log('💾 数据更新完成', {
          newCount: flattenComments.length,
          currentCommentId: this.data.currentCommentId
        });
      });
  
      // 如果当前正在查看这个评论，更新UI
      if (this.data.currentCommentId === commentId) {
        this.setData({
          currentSubComments: flattenComments
        });
        console.log('🔄 更新当前显示的子评论');
      }
  
    } catch (error) {
      console.error('获取子评论失败:', {
        error: error.message,
        stack: error.stack
      });
      this.setData({
        [`loadingSubComments.${commentId}`]: false
      });
      wx.showToast({ 
        title: '获取回复失败', 
        icon: 'none' 
      });
    } finally {
      console.groupEnd();
    }
  },
  // 时间格式化方法
  formatCommentTime(timeStr) {
    if (!timeStr) return '';
    const date = new Date(timeStr);
    const now = new Date();
    const diff = (now - date) / 1000; // 秒数差
    
    if (diff < 60) return '刚刚';
    if (diff < 3600) return `${Math.floor(diff/60)}分钟前`;
    if (diff < 86400) return `${Math.floor(diff/3600)}小时前`;
    
    return `${date.getMonth()+1}月${date.getDate()}日 ${date.getHours()}:${date.getMinutes().toString().padStart(2, '0')}`;
  },

  // 发送评论
  async submitComment() {
    if (this.data.submittingComment) return;
    const content = this.data.commentContent.trim();
    if (!content) {
      wx.showToast({ title: '评论内容不能为空', icon: 'none' });
      return;
    }
  
    this.setData({ submittingComment: true });
    
    try {
      const token = wx.getStorageSync('token');
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/v1/comments/${this.data.postInfo.id}`,
          method: 'POST',
          header: {
            'Authorization': `Bearer ${token}`
          },
          data: {
            content: content
          },
          success: resolve,
          fail: reject
        });
      });
  
      if (res.data.code !== '200' && res.data.code !== '0') {
        throw new Error(res.data.msg || '评论失败');
      }
  
      // 刷新评论列表
      this.setData({
        page: 1,
        nextCursor: '',
        hasMore: true,
        comments: []
      });
      await this.fetchComments();
      
      this.setData({
        commentContent: '',
        showCommentInput: false,
        submittingComment: false
      });
      
      wx.showToast({ title: '评论成功' });
    } catch (error) {
      console.error('评论失败:', error);
      this.setData({ submittingComment: false });
      wx.showToast({ 
        title: error.message || '评论失败', 
        icon: 'none' 
      });
    }
  },

  // 切换评论展开状态
  toggleCommentExpand(e) {
    const commentId = e.currentTarget.dataset.commentId;
    const isExpanded = this.data.expandedComments[commentId];
    
    if (!isExpanded) {
      // 如果还没有加载过子评论，则加载全部子评论
      if (!this.data.subCommentsMap[commentId]) {
        this.fetchAllSubComments(commentId);
        return;
      }
    }
    
    this.setData({
      [`expandedComments.${commentId}`]: !isExpanded
    });
  },

  // 点赞/取消点赞
  async toggleLike() {
    console.log('[toggleLike] 方法被调用'); // 基础日志
    
    if (this.data.likeLoading) {
      console.log('[toggleLike] 正在加载中，忽略本次点击');
      return;
    }
    
    this.setData({ likeLoading: true });
    console.log('[toggleLike] 设置likeLoading为true');
    
    try {
      console.log('[toggleLike] 开始调用API');
      const res = await this.callLikeApi();
      console.log('[toggleLike] API响应:', res);
      
      if (!res || !res.data) {
        throw new Error('API返回数据异常');
      }
      
      // 详细解析API响应
      console.log('[toggleLike] 完整响应数据:', JSON.stringify(res.data));
      
      const newStatus = res.data.data?.new_status;
      console.log('[toggleLike] 解析出的新状态:', newStatus);
      
      if (newStatus === undefined || newStatus === null) {
        throw new Error('API返回的状态无效');
      }
      
      // 确保状态是字符串类型
      const isLiked = String(newStatus);
      console.log('[toggleLike] 格式化后的状态:', isLiked);
      
      // 计算新的点赞数
      const oldLikeCount = this.data.postInfo.likeCount;
      const newLikeCount = isLiked === "1" ? oldLikeCount + 1 : Math.max(0, oldLikeCount - 1);
      console.log('[toggleLike] 点赞数变化:', `${oldLikeCount} -> ${newLikeCount}`);
      
      // 更新数据
      this.setData({
        isLiked: isLiked,
        'postInfo.likeCount': newLikeCount,
        likeLoading: false
      });
      console.log('[toggleLike] 数据更新完成');
      
      wx.showToast({
        title: isLiked === "1" ? '点赞成功' : '已取消',
        icon: 'none'
      });
      
    } catch (error) {
      console.error('[toggleLike] 发生错误:', error);
      this.setData({ likeLoading: false });
      wx.showToast({
        title: '操作失败: ' + (error.message || '未知错误'),
        icon: 'none'
      });
    }
  },
  

  // 监听评论输入
  onCommentInput(e) {
    console.log('输入内容:', e.detail.value) // 添加调试日志
    const content = e.detail.value
    if (content.length <= this.data.maxCommentLength) {
      this.setData({ commentContent: content })
    } else {
      // 超出字数限制时截取
      this.setData({
        commentContent: content.substring(0, this.data.maxCommentLength)
      })
      wx.showToast({
        title: `评论最多${this.data.maxCommentLength}字`,
        icon: 'none'
      })
    }
  },

  // 显示评论输入框
  showCommentInput() {
    // 使用nextTick确保状态更新后再设置focus
    wx.nextTick(() => {
      this.setData({ showCommentInput: true })
    })
  },

  // 隐藏评论输入框
  hideCommentInput() {
    this.setData({
      showCommentInput: false,
      commentContent: ''
    });
  },


  // 触底加载更多评论
  onReachBottom() {
    this.fetchComments()
  },

  // 预览图片
  previewImage(e) {
    if (this.data.mediaType === 'image') {
      const { url } = e.currentTarget.dataset
      wx.previewImage({
        current: url,
        urls: this.data.mediaList
      })
    }
  },

  

  // 修改时间格式化方法
  formatDate(timeStr) {
    console.log('[formatDate] 原始时间字符串:', timeStr); // 调试日志
    
    if (!timeStr) {
      console.warn('[formatDate] 警告: 时间字符串为空');
      return '';
    }
    
    try {
      // 处理可能的时区问题
      const normalizedTimeStr = timeStr.includes('T') ? timeStr : timeStr.replace(/-/g, '/');
      console.log('[formatDate] 标准化后时间字符串:', normalizedTimeStr); // 调试日志
      
      const date = new Date(normalizedTimeStr);
      console.log('[formatDate] 解析后的Date对象:', date); // 调试日志
      
      if (isNaN(date.getTime())) {
        console.error('[formatDate] 错误: 无效的日期对象');
        return '';
      }
      
      const year = date.getFullYear();
      const month = (date.getMonth() + 1).toString().padStart(2, '0');
      const day = date.getDate().toString().padStart(2, '0');
      const hours = date.getHours().toString().padStart(2, '0');
      const minutes = date.getMinutes().toString().padStart(2, '0');
      
      const formatted = `${year}-${month}-${day} ${hours}:${minutes}`;
      console.log('[formatDate] 格式化结果:', formatted); // 调试日志
      return formatted;
    } catch (error) {
      console.error('[formatDate] 格式化时间出错:', error);
      return '';
    }
  },

  // 统一的时间格式化方法（增加调试日志）
  formatTime(timeStr, type = 'comment') {
    console.log('[formatTime] 原始时间字符串:', timeStr, '类型:', type); // 调试日志
    
    if (!timeStr) {
      console.warn('[formatTime] 警告: 时间字符串为空');
      return '';
    }
    
    try {
      // 处理可能的时区问题
      const normalizedTimeStr = timeStr.includes('T') ? timeStr : timeStr.replace(/-/g, '/');
      console.log('[formatTime] 标准化后时间字符串:', normalizedTimeStr); // 调试日志
      
      const date = new Date(normalizedTimeStr);
      console.log('[formatTime] 解析后的Date对象:', date); // 调试日志
      
      if (isNaN(date.getTime())) {
        console.error('[formatTime] 错误: 无效的日期对象');
        return '';
      }
      
      if (type === 'comment') {
        const now = new Date();
        const diff = (now - date) / 1000; // 秒数差
        
        if (diff < 60) return '刚刚';
        if (diff < 3600) return `${Math.floor(diff/60)}分钟前`;
        if (diff < 86400) return `${Math.floor(diff/3600)}小时前`;
        
        const formatted = `${date.getMonth()+1}月${date.getDate()}日 ${date.getHours().toString().padStart(2, '0')}:${date.getMinutes().toString().padStart(2, '0')}`;
        console.log('[formatTime] 评论时间格式化结果:', formatted); // 调试日志
        return formatted;
      }
      
      // 默认返回完整时间
      const formatted = `${date.getFullYear()}-${(date.getMonth()+1).toString().padStart(2, '0')}-${date.getDate().toString().padStart(2, '0')} ${date.getHours().toString().padStart(2, '0')}:${date.getMinutes().toString().padStart(2, '0')}`;
      console.log('[formatTime] 完整时间格式化结果:', formatted); // 调试日志
      return formatted;
    } catch (error) {
      console.error('[formatTime] 格式化时间出错:', error);
      return '';
    }
  },

  // 更新当前时间
  updateTime() {
    const now = new Date();
    this.setData({
      currentTime: `${now.getHours().toString().padStart(2, '0')}:${now.getMinutes().toString().padStart(2, '0')}`
    });
  },

  // 显示子评论弹窗
// 显示子评论弹窗（带调试信息）
showSubCommentsPopup(e) {
  console.log('🎬 触发显示子评论事件', {
    event: e,
    dataset: e.currentTarget.dataset
  });

  const commentId = e.currentTarget.dataset.commentId;
  if (!commentId) {
    console.error('❌ 缺少commentId参数', e.currentTarget.dataset);
    return;
  }

  console.log('正在查找父评论:', {
    commentId,
    totalComments: this.data.comments.length
  });

  const comment = this.data.comments.find(c => c.id === commentId);
  if (!comment) {
    console.error('未找到父评论', {
      commentId,
      availableIds: this.data.comments.map(c => c.id)
    });
    return;
  }

  console.log('找到父评论:', {
    id: comment.id,
    content: comment.content,
    hasMore: comment.hasMore
  });

  console.log('[当前评论信息]',comment)
  this.setData({
    currentCommentId: commentId,
    currentComment: comment,
    showSubCommentsPopup: true
  }, () => {
    console.log('弹窗状态已更新');
    
    console.log('开始加载子评论');
    this.fetchAllSubComments(commentId).catch(err => {
      console.error('加载子评论失败:', err);
    })
  });
},


  // 隐藏子评论弹窗
  // 隐藏子评论弹窗（带调试信息）
hideSubCommentsPopup() {
  console.log('🛑 隐藏子评论弹窗', {
    currentCommentId: this.data.currentCommentId,
    showingCommentsCount: this.data.currentSubComments?.length || 0
  });

  this.setData({
    showSubCommentsPopup: false,
    currentCommentId: null,
    currentComment: null,
    currentSubComments: []
  });
},

  // 回复子评论
  onReplySubComment(e) {
    const commentId = e.currentTarget.dataset.commentId;
    const comment = this.data.currentSubComments.find(c => c.id === commentId);
    
    this.setData({
      replyingTo: comment.userName,
      replyingCommentId: commentId
    });
  },

  // 回复输入处理
  onReplyInput(e) {
    this.setData({
      replyContent: e.detail.value
    });
  },

  // 加载更多子评论
  async loadMoreSubComments() {
    if (!this.data.currentCommentId || !this.data.hasMoreSubComments) return;
    
    const commentId = this.data.currentCommentId;
    this.setData({
      [`loadingSubComments.${commentId}`]: true
    });

    try {
      const token = wx.getStorageSync('token');
      
      // 构建查询参数
      const params = {
        root_id: commentId,
        size: 50,
        lastCursor: this.data.son_lastCursor,
        sort: "id"
      };
      
      // 如果有last_id才添加该参数
      if (this.data.currentSubComments && this.data.currentSubComments.length > 0) {
        params.last_id = this.data.currentSubComments[this.data.currentSubComments.length - 1].id;
      }
      
      // 构建查询字符串
      const queryString = Object.keys(params)
        .map(key => `${encodeURIComponent(key)}=${encodeURIComponent(params[key])}`)
        .join('&');

      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/v1/comments/much?${queryString}`,
          method: 'GET',
          header: {
            'Authorization': `Bearer ${token}`
          },
          success: resolve,
          fail: reject
        });
      });

      // 后续处理保持不变...
      if (res.data.code !== '0' && res.data.code !== '200') {
        throw new Error(res.data.msg || '加载更多回复失败');
      }
      console.log('[获取到的更多评论原始数据]', newSubComments)
      const newSubComments = res.data.data?.data || res.data.data || [];
      const formattedComments = newSubComments.map(comment => ({
        id: comment.id,
        userId: comment.user_id || comment.userId,
        userName: comment.account,
        userAvatar: comment.avatar || comment.avater || '/images/default-avatar.jpg',
        content: comment.content,
        createTime: this.formatCommentTime(comment.create_time),
        parentId: comment.parent_id || commentId,
        isSubComment: true
      }));

      this.setData({
        [`subCommentsMap.${commentId}`]: [...(this.data.subCommentsMap[commentId] || []), ...formattedComments],
        currentSubComments: [...this.data.currentSubComments, ...formattedComments],
        son_lastCursor: res.data.data.nextCursor,
        hasMoreSubComments: !!res.data.data?.nextCursor,
        [`loadingSubComments.${commentId}`]: false
      });

    } catch (error) {
      console.error('加载更多回复失败:', error);
      this.setData({
        [`loadingSubComments.${commentId}`]: false
      });
      wx.showToast({ 
        title: '加载更多回复失败', 
        icon: 'none' 
      });
    }
  },
   // 空函数阻止冒泡
   noop() {}, 
   // 提交回复
   async submitReply() {
    console.group('提交回复');
    console.log('当前回复状态:', {
      replyingTo: this.data.replyingTo,
      commentId: this.data.replyingCommentId,
      contentLength: this.data.replyContent?.length || 0
    });
  
    if (!this.data.replyContent.trim()) {
      console.warn('内容为空，取消提交');
      wx.showToast({ title: '回复内容不能为空', icon: 'none' });
      console.groupEnd();
      return;
    }
  
    try {
      const token = wx.getStorageSync('token');
      const { postInfo, replyingCommentId, replyContent } = this.data;
  
      console.log('准备提交回复:', {
        postId: postInfo.id,
        parentId: replyingCommentId,
        contentPreview: replyContent.slice(0, 20) + (replyContent.length > 20 ? '...' : '')
      });
  
      const startTime = Date.now();
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: `https://${apiDomain}/api/v1/comments/${postInfo.id}`,
          method: 'POST',
          header: { 
            'Authorization': `Bearer ${token}`,
            'Content-Type': 'application/json'
          },
          data: {
            parent_id: replyingCommentId,
            content: replyContent
          },
          success: (res) => {
            console.log(`API响应 耗时:${Date.now() - startTime}ms`, {
              status: res.statusCode
            });
            resolve(res);
          },
          fail: (err) => {
            console.error('请求失败', err);
            reject(err);
          }
        });
      });
  
      console.log('完整响应:', res.data);
  
      if (res.data.code !== '200' && res.data.code !== '0') {
        const errMsg = res.data.msg || '回复失败';
        console.error('业务错误:', errMsg);
        throw new Error(errMsg);
      }
  
      console.log('回复成功，刷新评论列表');
      this.setData({
        page: 1,
        comments: [],
        hasMore: true
      });
  
      await this.fetchComments();
      this.hideReplyInput();
      wx.showToast({ title: '回复成功' });
  
    } catch (error) {
      console.error('回复失败:', {
        error: error.message,
        stack: error.stack
      });
      wx.showToast({ 
        title: error.message || '回复失败', 
        icon: 'none' 
      });
    } finally {
      console.groupEnd();
    }
  },

  handleLocationClick() {
    const { lat, lng, landmark } = this.data.postInfo;
    
    if (!lat || !lng) {
      wx.showToast({
        title: '位置信息不完整',
        icon: 'none'
      });
      return;
    }

    // 方法1：直接打开微信地图
    this.openWechatMap(lat, lng, landmark);
  },
  
  // 方法1：调用微信内置地图
  openWechatMap(latitude, longitude, name) {
    console.log(latitude, longitude, name)
    wx.openLocation({
      latitude: parseFloat(latitude),
      longitude: parseFloat(longitude),
      name: name || '目标位置',
      scale: 18,
      success: (res) => {
        console.log('打开地图成功', res);
      },
      fail: (err) => {
        console.error('打开地图失败', err);
        wx.showToast({
          title: '打开地图失败',
          icon: 'none'
        });
      }
    });
  },

// 轮播图切换事件
  onSwiperChange(e) {
    this.setData({
      currentSwiperIndex: e.detail.current
    });
  },
  // 分享
  onShareAppMessage() {
    return {
      title: this.data.title,
      path: `/pages/blog_detail/blog_detail?id=${this.data.id}`
    }
  },
  onBackClick() {
    wx.navigateBack();
  },
  onUnload() {
    // 页面卸载时清理临时文件
    Object.values(this.data.tempFilePaths).forEach(tempFilePath => {
      wx.getFileSystemManager().unlink({
        filePath: tempFilePath,
        fail: (err) => console.warn('删除临时文件失败:', err)
      });
    });
  }
})