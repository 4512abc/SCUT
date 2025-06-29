function msg(type, msg) {
  Vue.prototype.$message({
    type: type,
    message: msg,
    duration: 2000,
    offset: 100,
    center: true,
  });
}

let wrapper = new Vue({
  el: "#wrapper",
  data: {
    currentUser: {},
    info4Search: {
      title: "",
      type: 1,
      startTime: "",
      endTime: "",
    },
    objs: [],
    pageInfo: {
      pageNum: 1,
      pageSize: 10,
      total: 0,
      hasNextPage: false,
    },
    preActive: false,
    nextActive: false,
    showDetail: false,
    showEdit: false,
    selectedAnnouncement: {
      id: null,
      title: "",
      content: "",
      type: 1,
      createTime: "",
      updateTime: "",
      published_id: null, // 添加发布者ID
      user_account: "", // 添加发布者账号
    },
    editingAnnouncement: {
      id: null,
      title: "",
      content: "",
      type: 1,
    },
    editQuill: null,
  },
  created: function () {
    if (!window.checkLogin()) return; // 添加登录验证
    try {
      const currentUser = localStorage.getItem("currentUser");
      this.currentUser = currentUser ? JSON.parse(currentUser) : {}; // 添加安全解析
    } catch (e) {
      this.currentUser = {}; // 异常时使用空对象避免崩溃
      console.error("用户信息解析失败:", e);
    }
    this.loadTable(1); // 默认加载第一页数据
  },
  methods: {
    goToPage(page) {
      location.href = page + ".html";
    },

    formatDateTime(date) {
      if (!date) return "";
      // 将日期格式化为 YYYY-MM-DD HH:mm:ss
      return `${date} ${"00:00:00"}`;
    },
    /**
     * 加载表单
     * */
    loadTable: function (pageNum) {
      // 构造请求参数
      const params = {
        pageSize: this.pageInfo.pageSize || 10,
        pageNum: pageNum || this.pageInfo.pageNum || 1,
        title: this.info4Search.title || "",
        startTime: this.formatDateTime(this.info4Search.startTime) || "",
        endTime: this.formatDateTime(this.info4Search.endTime) || "",
        type: this.info4Search.type,
      };

      // 构造查询字符串
      const queryString = new URLSearchParams(params).toString();

      // 修正API路径
      axios
        .get(
          `https://scutdionysus.cn/api/admin/announcements/search?${queryString}`
        )
        .then((res) => {
          if (res.data.code === "0") {
            // 确保数据正确获取和赋值
            if (res.data.data && Array.isArray(res.data.data.list)) {
              this.objs = res.data.data.list;
              this.updatePageInfo(res.data.data);
              console.log("公告数据:", this.objs);
            } else {
              console.error("返回数据格式不正确:", res.data);
              msg("error", "数据格式错误");
            }
          } else {
            msg("error", res.data.msg || "获取数据失败");
          }
        })
        .catch((error) => {
          console.error("请求失败:", error);
          msg("error", "加载失败：" + error.message);
        });
    },

    updatePageInfo(data) {
      if (!data) return;

      this.pageInfo = {
        pageNum: data.pageNum || 1,
        pageSize: data.pageSize || 10,
        total: data.total || 0,
        hasNextPage: data.hasNextPage,
      };

      // 更新翻页按钮状态
      this.preActive = this.pageInfo.pageNum <= 1;
      this.nextActive = !this.pageInfo.hasNextPage;
    },

    // 格式化时间
    formatTime(time) {
      if (!time) return "";
      return new Date(time).toLocaleString();
    },

    edit(item) {
      this.showEdit = true;
      this.showDetail = false;

      // 加载公告详情
      axios
        .get(`https://scutdionysus.cn/api/auth/announcement_info/${item.id}`, {
          headers: {
            Authorization: this.currentUser.token,
          },
        })
        .then((res) => {
          if (res.data.code === "0") {
            this.editingAnnouncement = {
              id: item.id,
              title: res.data.data.title,
              content: res.data.data.content,
              type: res.data.data.type,
            };

            // 等待DOM更新后初始化编辑器
            this.$nextTick(() => {
              if (this.editQuill) {
                try {
                  this.editQuill.destroy();
                } catch (e) {
                  console.error("销毁编辑器失败:", e);
                }
              }

              const editorContainer = document.querySelector("#editEditor");
              if (!editorContainer) {
                console.error("找不到编辑器容器");
                return;
              }

              // 重新初始化编辑器
              this.editQuill = new Quill("#editEditor", {
                modules: {
                  toolbar: [
                    [{ header: [1, 2, 3, 4, 5, 6, false] }],
                    [{ font: [] }],
                    ["bold", "italic", "underline", "strike"],
                    [{ align: [] }],
                    ["blockquote", "code-block"],
                    [{ color: [] }, { background: [] }],
                    ["clean"],
                    ["image", "link", "video"],
                  ],
                },
                theme: "snow",
              });

              // 设置编辑器内容
              if (this.editingAnnouncement.content) {
                this.editQuill.root.innerHTML =
                  this.editingAnnouncement.content;
              }
            });

            msg("success", "加载公告详情成功");
          } else {
            msg("error", res.data.msg || "获取公告详情失败");
          }
        })
        .catch((error) => {
          console.error("加载公告详情失败:", error);
          msg("error", "加载失败：" + error.message);
        });
    },

    saveEdit() {
      if (!this.editingAnnouncement.title.trim()) {
        msg("error", "标题不能为空");
        return;
      }

      const content = this.editQuill.root.innerHTML;
      if (!content.trim()) {
        msg("error", "内容不能为空");
        return;
      }

      const postData = {
        title: this.editingAnnouncement.title,
        content: content,
      };

      axios
        .post(
          `https://scutdionysus.cn/api/admin/announcements/${this.editingAnnouncement.id}/modify`,
          postData,
          {
            headers: {
              Authorization: this.currentUser.token,
              "Content-Type": "application/json",
            },
          }
        )
        .then((res) => {
          if (res.data.code === "0") {
            msg("success", "更新成功");
            this.backToList();
            this.loadTable(this.pageInfo.pageNum); // 刷新列表
          } else {
            msg("error", res.data.msg || "更新失败");
          }
        })
        .catch((error) => {
          console.error("更新失败:", error);
          msg("error", "更新失败：" + error.message);
        });
    },

    viewDetail(announcement) {
      this.showDetail = true;
      // 先使用列表中的基本信息
      this.selectedAnnouncement = { ...announcement };

      // 加载完整的公告详情
      const fullUrl = `https://scutdionysus.cn/api/auth/announcement_info/${announcement.id}`;
      console.log("加载公告详情的URL:", fullUrl);
      axios
        .get(
          `https://scutdionysus.cn/api/auth/announcement_info/${announcement.id}`,
          {
            headers: {
              Authorization: this.currentUser.token,
            },
          }
        )
        .then((res) => {
          if (res.data.code === "0") {
            this.selectedAnnouncement = {
              ...this.selectedAnnouncement,
              ...res.data.data,
            };
            msg("success", "加载公告详情成功");
          } else {
            msg("error", res.data.msg || "获取公告详情失败");
          }
        })
        .catch((error) => {
          console.error("加载公告详情失败:", error);
          msg("error", "加载失败：" + error.message);
        });
    },

    backToList() {
      if (this.editQuill) {
        try {
          this.editQuill.destroy();
        } catch (e) {
          console.error("销毁编辑器失败:", e);
        }
        this.editQuill = null;
      }

      this.showDetail = false;
      this.showEdit = false;
      this.editingAnnouncement = {
        id: null,
        title: "",
        content: "",
        type: 1,
      };

      // 刷新列表
      this.loadTable(this.pageInfo.pageNum);
    },
  },
});
