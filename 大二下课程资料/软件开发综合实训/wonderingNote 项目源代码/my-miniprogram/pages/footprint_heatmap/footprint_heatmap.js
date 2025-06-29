import { apiDomain } from "../../config";

Page({
  data: {
    center: { longitude: 116.397470, latitude: 39.908170 },
    markers: [],
    showBlogList: false,
    selectedLocation: null,
    showLoading: false,
    locationBlogs: [],
    totalPlaces: 0,
    totalBlogs: 0,
    totalLikes: 0,
    mapHeight: 400,
    showPlacesPopup: false, // 控制地点列表弹窗显示
    placesList: [],        // 地点列表数据  
    activePlaceId: null,    // 当前选中的地点ID
    is_other: false,
    selectingMarker: 0
  },

  onLoad() {
    const systemInfo = wx.getSystemInfoSync();
    this.setData({ mapHeight: systemInfo.windowHeight * 0.65 });
    this.loadPlaces();
    console.log('页面加载，开始获取统计数据');
    this.loadBlogStats();
    
    const savedTheme = wx.getStorageSync('theme') || 0;
    this.setTheme(savedTheme);
    
  },
  onShow(){
    Promise.all([
      this.loadPlaces(),
      this.loadBlogStats()
    ])
  },

  async loadPlaces() {
    this.setData({ showLoading: true });

    const fetchPlaces = () => {
      return new Promise((resolve, reject) => {
        wx.request({
          url: 'https://' + apiDomain + '/api/footprint/landmarkList',
          method: 'GET',
          header: {
            Authorization: wx.getStorageSync('token') || ''
          },
          success: (res) => {
            if (res.statusCode === 200 && res.data.code === '0') {
              resolve(res.data.data.data);
              console.log(res.data.data)
            } else {
              reject(new Error(res.data.msg || '请求失败'));
            }
          },
          fail: (error) => {
            reject(error);
          }
        });
      });
    };

    try {
      const data = await fetchPlaces();

      if (Array.isArray(data) && data.length > 0) {
        const markers = data.map((item, index) => ({
          id: item.id || index, // 优先使用item.id，没有则用index
          latitude: item.location.lat,
          longitude: item.location.lng,
          title: item.landmarkName || item.landmark_name, // 兼容两种命名
          width: 32,
          height: 32,
          callout: {
            content: item.landmarkName || item.landmark_name || '未知地点',
            padding: 8,
            borderRadius: 4,
            display: 'BYCLICK',
            fontSize: 12,
            bgColor: '#ffffff',
            textAlign: 'center'
          }
        }));

        this.setData({
          center: {
            latitude: data[0].location.lat,
            longitude: data[0].location.lng
          },
          markers,
          places: data,
          totalPlaces: data.length
        });

        const points = data.map(item => ({
          latitude: item.location.lat,
          longitude: item.location.lng
        }));

        const mapContext = wx.createMapContext('myMap', this);
        mapContext.includePoints({
          points,
          padding: [50]
        });
        console.log(data)
      } else {
        throw new Error('返回数据格式错误或为空');
      }
    } catch (error) {
      console.error('加载地点失败:', error);
    } finally {
      this.setData({ showLoading: false });
    }
  },

  async onMarkerTap(e) {
    console.log('[DEBUG] 标记点点击事件:', e); // 调试日志
    
    try {
      const markerId = e.markerId;
      console.log('[DEBUG] 点击的标记点ID:', markerId);
      this.setData({
        selectingMarker: markerId
      })
      // 确保places数据存在
      if (!this.data.places || !this.data.places.length) {
        console.error('地点数据未加载或为空');
        return;
      }
      
      // 查找对应的地点 - 更安全的查找方式
      const place = this.data.places.find(p => p.id === markerId) || this.data.places[markerId];
      
      if (!place) {
        console.error('未找到对应的地点数据');
        return;
      }
      
      console.log('[DEBUG] 找到的地点数据:', place);
      
      // 使用更兼容的属性访问方式
      const landmarkName = place.landmarkName || place.landmark_name;
      
      if (!landmarkName) {
        console.error('地点名称不存在');
        return;
      }
      
      this.setData({
        selectedLocation: {
          ...place,
          title: landmarkName // 确保有title属性供模板使用
        },
        showBlogList: true
      });
      console.log(place)
      console.log(landmarkName, place.location.lat, place.location.lng)
      await this.loadPlaceBlogs(landmarkName, place.location.lat, place.location.lng);
      
    } catch (error) {
      console.error('标记点点击处理失败:', error);
      wx.showToast({
        title: '加载失败，请重试',
        icon: 'none'
      });
    }
  },
  toggleUserBlogs(){
    this.setData({
      is_other: !this.data.is_other
    })
    console.log(this.data.selectingMarker)
    const place = this.data.places.find(p => p.id === this.data.selectingMarker) || this.data.places[this.data.selectingMarker];
    
    console.log(place)
    this.loadPlaceBlogs(this.data.selectedLocation.title, place.location.lng, place.location.lat)
  },

  async loadPlaceBlogs(landmarkName, lat, lng) {
    console.log('加载博客请求，地标名称：', landmarkName,
                '地点维度、经度', lat, lng);
    
    if (!landmarkName) {
      console.error('地标名称为空，无法加载博客');
      return;
    }

    this.setData({ showLoading: true });

    let url = ''
    if(this.data.is_other){
      url = 'https://' + apiDomain + '/api/footprint/other_blogs'
    }
    else{
      url = 'https://' + apiDomain + '/api/footprint/user_blogs'
    }
    const fetchBlogs = () => {
      console.log('[正在加载博文中心位置]', lat, lng)
      return new Promise((resolve, reject) => {
        wx.request({
          url: url,
          method: 'GET',
          header: {
            Authorization: wx.getStorageSync('token') || ''
          },
          data: {
            landmark_name: landmarkName,
            size: 10,
            sort: 'id',
            lastCursor: "0",
            lat: lat,
            lng: lng,
            range: 300000
          },
          success: (res) => {
            if (res.statusCode === 200 && (res.data.code === '200' || res.data.code === '0')) {
              resolve(res.data.data.data);
            } else {
              reject(new Error(res.data.msg || '请求失败'));
            }
          },
          fail: (err) => {
            reject(err);
          }
        });
      });
    };

    try {
      const blogs = await fetchBlogs();
      console.log(blogs)

      const processedBlogs = blogs.map(blog => {
        let coverUrl = '/static/images/default-blog-cover.jpg'; // 默认封面
        
        try {
          // 只有cover有值且不是"{}"时才处理
          if (blog.cover && blog.cover !== '{}') {
            const coverData = JSON.parse(blog.cover);
            console.log(coverData)
            console.log(coverData.url)
            if (coverData.url) {
              // 拼接完整URL
              coverUrl = `http://${apiDomain}:8888${coverData.url}`;
            }
          }
        } catch (e) {
          console.error('解析cover失败:', blog.cover);
        }
        
        return {
          ...blog,
          cover: coverUrl  // 添加处理后的封面URL
        };
      });

      this.setData({ locationBlogs: processedBlogs });
      console.log(this.data.locationBlogs)
    } catch (error) {
      console.error('加载博客列表失败:', error);
    } finally {
      this.setData({ showLoading: false });
    }
  },

  // 新增方法 - 获取博文统计
  async loadBlogStats() {
    console.log('[loadBlogStats] 开始获取统计数据');
    wx.showLoading({ title: '加载中...' });
    
    try {
      const res = await this.fetchBlogs(1000);
      console.log('[loadBlogStats] 请求返回数据:', res);
      
      if (res && res.code === '0') {
        const blogs = res.data?.data || [];
        console.log('[loadBlogStats] 获取到的博文数据:', blogs);
        
        const totalBlogs = blogs.length;
        const totalLikes = blogs.reduce((sum, blog) => sum + (blog.like_count || 0), 0);
        
        console.log(`[loadBlogStats] 统计结果: 博文数=${totalBlogs}, 点赞数=${totalLikes}`);
        
        this.setData({ 
          totalBlogs,
          totalLikes 
        }, () => {
          console.log('[loadBlogStats] 数据已更新到界面');
        });
      } else {
        const errMsg = res?.msg || '未知错误';
        console.error('[loadBlogStats] 接口返回错误:', errMsg);
        wx.showToast({ title: `数据错误: ${errMsg}`, icon: 'none' });
      }
    } catch (error) {
      console.error('[loadBlogStats] 捕获到异常:', error);
      wx.showToast({ 
        title: '加载失败，请重试', 
        icon: 'none',
        duration: 2000
      });
    } finally {
      wx.hideLoading();
      console.log('[loadBlogStats] 统计流程结束');
    }
  },

  // 分页请求封装（增强版）
  fetchBlogs(size = 1000) {
    console.log(`[fetchBlogs] 准备请求数据，size=${size}`);
    const token = wx.getStorageSync('token') || '';
    
    return new Promise((resolve, reject) => {
      wx.request({
        url: `https://${apiDomain}/api/auth/posts_info`,
        method: 'GET',
        data: {
          size,
          sort: 'id',
          lastCursor: '0',
        },
        header: {
          'Authorization': token,
          'Content-Type': 'application/json'
        },
        success: (res) => {
          console.log('[fetchBlogs] 请求成功，状态码:', res.statusCode, '返回数据:', res.data);
          
          if (res.statusCode === 200) {
            if (res.data.code === '0') {
              resolve(res.data);
            } else {
              console.error('[fetchBlogs] 业务逻辑错误:', res.data);
              reject(new Error(res.data?.msg || '业务逻辑错误'));
            }
          } else {
            console.error('[fetchBlogs] HTTP错误:', res.statusCode);
            reject(new Error(`HTTP错误: ${res.statusCode}`));
          }
        },
        fail: (err) => {
          console.error('[fetchBlogs] 请求失败:', err);
          reject(new Error('网络请求失败'));
        }
      });
    });
  },

  navigateToBlog(e) {
    const blogId = e.currentTarget.dataset.blogId;
    wx.navigateTo({
      url: `/pages/interaction/blog/blog_detail/blog_detail?id=${blogId}`
    });
  },

  navigateToMyBlog(){
    wx.navigateTo({
      url: '/pages/my/my_blog/my_blog',
    })
  },

  navigateToMyLike(){
    wx.navigateTo({
      url: '/pages/my/message_center/message_center',
    })
  },

  onPopupClose() {
    console.log('关闭模态框，当前 showBlogList 状态:', this.data.showBlogList);
    this.setData({
      showBlogList: false,
      selectedLocation: null,
      locationBlogs: [],
      is_other: false
    });
  },
  // 改进的随机位置算法（避免重叠）
generateRandomPositions(count) {
  const positions = [];
  const gridSize = 10; // 将区域划分为10x10网格
  
  for (let i = 0; i < count; i++) {
    let attempts = 0;
    let pos;
    
    do {
      pos = {
        top: 10 + Math.floor(Math.random() * 7) * 10, // 10%-80%
        left: 25 + Math.floor(Math.random() * 7) * 10 // 20%-80%
      };
      attempts++;
    } while (
      attempts < 100 && 
      positions.some(p => 
        Math.abs(p.top - pos.top) < 15 && 
        Math.abs(p.left - pos.left) < 15
      )
    );
    
    positions.push(pos);
  }
  
  return positions;
},
showPlaces() {
  const { places } = this.data;
  
  if (!places || places.length === 0) {
    wx.showToast({ title: '暂无地点数据', icon: 'none' });
    return;
  }

  // 生成随机位置
  const positions = this.generateRandomPositions(places.length);
  
  const placesList = places.map((place, index) => ({
    id: place.id || index,
    name: place.landmarkName || place.landmark_name || '未知地点',
    randomTop: positions[index].top,
    randomLeft: positions[index].left
  }));

  this.setData({ 
    showPlacesPopup: true,
    placesList,
    showBlogList: false, // 确保博文弹窗关闭
    activePlaceId: null  // 重置选中状态
  });
},

// 点击地点项
onPlaceItemTap(e) {
  const { id } = e.currentTarget.dataset;
  const { places } = this.data;
  
  // 1. 设置选中状态
  this.setData({ activePlaceId: id });
  
  // 2. 找到对应地点
  const place = places.find(p => (p.id || p.id === 0) ? p.id === id : places.indexOf(p) === id);
  if (!place) return;

  // 3. 移动地图中心
  this.setData({
    center: {
      latitude: place.location.lat,
      longitude: place.location.lng
    },
    showPlacesPopup: false
  });

  // 4. 显示博文弹窗（会自动隐藏地点卡片）
  this.onMarkerTap({
    markerId: id,
    type: 'tap',
    detail: {}
  });

},

// 关闭地点弹窗
closePlacesPopup() {
  this.setData({ 
    showPlacesPopup: false,
    activePlaceId: null
  });
},

// 在博文弹窗关闭时恢复地点卡片显示
onPopupClose() {
  this.setData({
    showBlogList: false,
    selectedLocation: null,
    locationBlogs: [],
    is_other: false
    // activePlaceId 保持以保持高亮
  });
},
});
