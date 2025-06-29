const { apiDomain } = require("../../config");


Page({
  data: {
    monthList: [],
    notes: [],
    allNotes: [], // 新增：存储所有博文数据
    formatter: null,
    currentYear: new Date().getFullYear(),
    currentMonth: new Date().getMonth() + 1,
    currentMonthIndex: 1,
    isLoading: false,
    isLoadingMonth: false,
    formatter: day => day,
  },

  onLoad() {
    this.initMonthList();
    this.initFormatter();
    this.loadAllNotes(); // 修改：改为加载所有博文

    const savedTheme = wx.getStorageSync('theme') || 0;
    this.setTheme(savedTheme);
  },

  onShow(){
    this.loadAllNotes()
  },

  initMonthList() {
    const now = new Date();
    const currentYear = now.getFullYear();
    const currentMonth = now.getMonth(); // 0-based
  
    // 只加载当前月
    const monthDate = new Date(currentYear, currentMonth, 1);
    const endDate = new Date(currentYear, currentMonth + 1, 0);
  
    const currentItem = {
      startDate: monthDate.getTime(),
      endDate: endDate.getTime(),
      defaultDate: monthDate.getTime(),
      year: currentYear,
      month: currentMonth + 1
    };
  
    this.setData({
      monthList: [currentItem],
      currentMonthIndex: 0
    });
  
    // 异步加载其他月份视图（不影响初始渲染）
    setTimeout(() => {
      this.loadSurroundingMonths(currentYear, currentMonth);
    }, 0);
  },

  // 补齐前后 6 个月
  loadSurroundingMonths(year, month) {
    const months = [];
  
    // 向前6个月
    for (let i = 6; i >= 1; i--) {
      const d = new Date(year, month - i, 1);
      months.push({
        startDate: d.getTime(),
        endDate: new Date(d.getFullYear(), d.getMonth() + 1, 0).getTime(),
        defaultDate: d.getTime(),
        year: d.getFullYear(),
        month: d.getMonth() + 1
      });
    }
  
    // 当前月（已存在，不加）
  
    // 向后6个月
    for (let i = 1; i <= 6; i++) {
      const d = new Date(year, month + i, 1);
      months.push({
        startDate: d.getTime(),
        endDate: new Date(d.getFullYear(), d.getMonth() + 1, 0).getTime(),
        defaultDate: d.getTime(),
        year: d.getFullYear(),
        month: d.getMonth() + 1
      });
    }
  
    // 插入视图：当前月在中间，更新 currentMonthIndex
    const finalMonthList = [...months.slice(0, 6), this.data.monthList[0], ...months.slice(6)];
  
    this.setData({
      monthList: finalMonthList,
      currentMonthIndex: 6 // 中间位置
    });
  },

  // 新增方法：加载所有博文数据
  async loadAllNotes() {
    try {
      this.setData({ isLoading: true });
      console.log('[loadAllNotes] 请求开始');
  
      const result = await new Promise((resolve, reject) => {
        wx.request({
          url: 'https://' + apiDomain + '/api/auth/posts_info',
          method: 'GET',
          data: {
            size: 1000,
            lastCursor: "0"
          },
          header: {
            'Content-Type': 'application/json',
            'Authorization': wx.getStorageSync('token') || ''
          },
          success: res => resolve(res.data),
          fail: err => reject(err)
        });
      });
  
      console.log('[loadAllNotes] 接口返回:', result);
  
      if (result.code === '200' || result.code === '0') {
        console.log('[loadAllNotes] 博文原始数据:', result.data.data);
        const formattedNotes = result.data.data.map(note => {
          console.log('处理note:', note);
          const date = new Date(note.create_time);
          const year = date.getFullYear();
          const month = String(date.getMonth() + 1).padStart(2, '0');
          const day = String(date.getDate()).padStart(2, '0');
          return {
            ...note,
            year,
            month: parseInt(month),
            day,
            formattedDate: `${year}-${month}-${day}`  // ✅ 新增字段用于显示
          };
        });
  
        console.log('[loadAllNotes] 格式化后的博文:', formattedNotes);
  
        const { currentYear, currentMonth } = this.data;
        const filtered = formattedNotes.filter(note =>
          note.year === currentYear && note.month === currentMonth
        );
        console.log(`[loadAllNotes] 当前 ${currentYear}-${currentMonth} 筛选结果:`, filtered);
  
        this.setData({
          allNotes: formattedNotes,
          notes: filtered
        });
  
        this.updateFormatter();
      } else {
        console.warn('[loadAllNotes] 非200响应:', result);
        wx.showToast({
          title: '加载失败',
          icon: 'none'
        });
      }
    } catch (error) {
      console.error('[loadAllNotes] 异常:', error);
      wx.showToast({
        title: '加载失败',
        icon: 'none'
      });
    } finally {
      this.setData({ isLoading: false });
    }
  },

  // 新增方法：格式化博文数据
  formatNotesData(notes) {
    return notes.map(note => {
      // 假设note中有create_time字段，格式为"YYYY-MM-DD"
      const dateParts = note.create_time.split('-');
      return {
        ...note,
        year: parseInt(dateParts[0]),
        month: parseInt(dateParts[1]),
        day: parseInt(dateParts[2]),
        date: note.create_time // 保持原始日期字符串
      };
    });
  },

  // 新增方法：按月筛选博文
  filterNotesByMonth(notes, year, month) {
    return notes.filter(note => 
      note.year === year && note.month === month
    );
  },

  // 修改原loadMonthNotes方法为前端筛选
  updateMonthNotes() {
    const { allNotes, currentYear, currentMonth } = this.data;
    this.setData({
      notes: this.filterNotesByMonth(allNotes, currentYear, currentMonth)
    }, () => {
      this.initFormatter(); // ✅ 回调中执行
    });
  },

  // 修改onMonthChange方法
  async onMonthChange(e) {
    const index = e.detail.current;
    const { monthList, currentMonthIndex } = this.data;
    
    const currentMonth = monthList[index];
    if (currentMonth) {
      // 只在 currentMonthIndex 发生变化时更新
      if (index !== currentMonthIndex) {
        this.setData({
          currentYear: currentMonth.year,
          currentMonth: currentMonth.month,
          currentMonthIndex: index
        });
        this.updateMonthNotes();
      }
    }
  
    // 滑到最前或最后时，弹出对话框
    if (index === 0 || index === monthList.length - 1) {
      const direction = index === 0 ? 'prev' : 'next';
      wx.showModal({
        title: '查看更多月份',
        content: direction === 'prev' ? '是否加载更早的博文？' : '是否加载更晚的博文？',
        success: (res) => {
          if (res.confirm) {
            this.loadMoreMonths(direction);
          }
        }
      });
    }
  },

  async loadMoreMonths(direction) {
    const { monthList, currentMonthIndex } = this.data;
    let newMonths = [];
    
    if (direction === 'prev') {
      const firstMonth = monthList[0];
      let year = firstMonth.year;
      let month = firstMonth.month - 4;
      
      while (month < 0) {
        month += 12;
        year--;
      }
  
      for (let i = 0; i < 3; i++) {
        const d = new Date(year, month + i, 1);
        newMonths.push({
          startDate: d.getTime(),
          endDate: new Date(d.getFullYear(), d.getMonth() + 1, 0).getTime(),
          defaultDate: d.getTime(),
          year: d.getFullYear(),
          month: d.getMonth() + 1
        });
      }
      
      // 仅修改视图和 monthList，避免重新设置 currentMonthIndex
      this.setData({
        monthList: [...newMonths, ...monthList]
      });
    } else {
      const lastMonth = monthList[monthList.length - 1];
      let year = lastMonth.year;
      let month = lastMonth.month;
  
      for (let i = 1; i <= 3; i++) {
        if (month + i > 12) {
          month -= 12;
          year++;
        }
  
        const d = new Date(year, month + i - 1, 1);
        newMonths.push({
          startDate: d.getTime(),
          endDate: new Date(d.getFullYear(), d.getMonth() + 1, 0).getTime(),
          defaultDate: d.getTime(),
          year: d.getFullYear(),
          month: d.getMonth() + 1
        });
      }
  
      // 仅修改视图和 monthList，避免重新设置 currentMonthIndex
      this.setData({
        monthList: [...monthList, ...newMonths]
      });
    }
  },

  // 新增方法：跳转到详情页
  navigateToDetail(e) {
    console.group('=== 点击事件调试 ===');
    console.log('[事件对象]', e);
    console.log('[dataset]', e.currentTarget.dataset);
    
    const postId = e.currentTarget.dataset.id;
    console.log('[获取到的ID]', postId);
    
    if (!postId) {
      console.warn('ID不存在，检查数据绑定');
      wx.showToast({ title: '数据加载中，请稍后', icon: 'none' });
      return;
    }
  
    wx.navigateTo({
      url: `/pages/interaction/blog/blog_detail/blog_detail?id=${postId}`,
      success: () => console.log('跳转成功'),
      fail: (err) => {
        console.error('跳转失败:', err);
        wx.showToast({ title: '跳转失败', icon: 'none' });
      }
    });
    console.groupEnd();
  },

  initFormatter() {
    const today = new Date();
    
    this.setData({
      formatter: (day) => {
        const isToday = day.date.getFullYear() === today.getFullYear() &&
                        day.date.getMonth() === today.getMonth() &&
                        day.date.getDate() === today.getDate();
    
        const dateStr = this.formatDate(day.date);
        const hasNote = this.data.notes.some(note => note.formattedDate === dateStr);

        return {
          ...day,
          className: isToday ? 'today' : hasNote ? 'has-note' : ''
        };
      }
    });
  },

  formatDate(date) {
    return `${date.getFullYear()}-${String(date.getMonth() + 1).padStart(2, '0')}-${String(date.getDate()).padStart(2, '0')}`;
  },

  updateFormatter() {
    const formatter = this.data.formatter;
    this.setData({ formatter: null }, () => {
      this.setData({ formatter });
    });
  }


  // navigateToWrite() {
  //   wx.navigateTo({
  //     url: '/pages/interaction/blog/blog_create/blog_create'
  //   });
  // },

  // navigateToChallenge() {
  //   wx.navigateTo({
  //     url: '/pages/interaction/challenge/create_challenge/create_challenge'
  //   });
  // }
});