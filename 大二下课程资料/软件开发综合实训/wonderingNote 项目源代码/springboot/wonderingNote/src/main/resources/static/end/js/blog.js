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
    objs: [],
    pageInfo: {
      pageNum: 1,
      pageSize: 8,
      total: 0,
      hasNextPage: false,
    },
    searchTitle: "",
    startDate: "",
    endDate: "",
    preActive: false,
    nextActive: false,
    showPostDetail: false,
    selectedPost: {
      initial_info: {
        user_account: "",
        id: "",
        user_avatar: null,
      },
      post_list: {
        id: null,
        cover: null,
        title: "",
        view_count: 0,
        like_count: 0,
        comment_count: 0,
        create_time: "",
        location: {
          lng: null,
          lat: null,
        },
        landmark_name: "",
      },
      details: {
        content: "",
        images: [],
        videos: null,
      },
    },
    previewDialogVisible: false,
    previewImageUrl: "",
  },
  created: function () {
    if (!window.checkLogin()) return; // 添加登录验证
    try {
      const currentUser = localStorage.getItem("currentUser");
      this.currentUser = currentUser ? JSON.parse(currentUser) : {};

      // 获取 URL 参数中的 postId
      const urlParams = new URLSearchParams(window.location.search);
      const postId = urlParams.get("postId");

      // 如果存在 postId，直接展示博文详情
      if (postId) {
        this.viewDetail(postId);
      }
    } catch (e) {
      this.currentUser = {};
      console.error("用户信息解析失败:", e);
    }
    this.loadTable(1);
  },
  methods: {
    // 添加处理图片URL的方法
    getPostImageUrl(imageJson) {
      if (!imageJson) return "";

      try {
        const imageData = JSON.parse(imageJson);
        return imageData && imageData.id
            ? `https://scutdionysus.cn/api/files/${imageData.id}/download`
            : "";
      } catch (e) {
        console.error("解析图片数据失败:", e);
        return "";
      }
    },

    formatDateTime(dateStr) {
      if (!dateStr) return "";
      const date = new Date(dateStr);
      const year = date.getFullYear();
      const month = String(date.getMonth() + 1).padStart(2, "0");
      const day = String(date.getDate()).padStart(2, "0");
      const hours = String(date.getHours()).padStart(2, "0");
      const minutes = String(date.getMinutes()).padStart(2, "0");
      const seconds = String(date.getSeconds()).padStart(2, "0");
      return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
    },
    /**
     * 加载表单
     * */
    loadTable: function (pageNum) {
      // 构造请求参数
      const params = {
        pageNum: pageNum || this.pageInfo.pageNum || 1,
        pageSize: this.pageInfo.pageSize || 10,
        title: this.searchTitle || "",
        startTime: this.formatDateTime(this.startDate) || "",
        endTime: this.formatDateTime(this.endDate) || "",
      };

      // 构造查询字符串
      const queryParams = new URLSearchParams(params);
      const fullUrl = `https://scutdionysus.cn/api/admin/posts/search?${queryParams.toString()}`;

      console.log("请求的URL:", fullUrl); // 调试输出请求的URL
      // 发送请求
      axios
          .get(fullUrl)
          .then((res) => {
            if (res.data.code === "0") {
              this.objs = res.data.data.list;
              this.updatePageInfo(res.data.data);
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
      this.pageInfo = {
        pageNum: data.pageNum || 1,
        pageSize: this.pageInfo.pageSize || 10,
        total: data.total || 0,
        hasNextPage: data.hasNextPage || false,
      };
      this.preActive = this.pageInfo.pageNum <= 1;
      this.nextActive = !this.pageInfo.hasNextPage;
    },

    searchPosts() {
      this.loadTable(1); // 搜索时重置到第一页
    },

    del(id) {
      this.$confirm("确认删除该博文?", "提示", {
        confirmButtonText: "确定",
        cancelButtonText: "取消",
        type: "warning",
      })
          .then(() => {
            // 修改删除请求
            axios
                .delete(
                    `https://scutdionysus.cn/api/posts/${id}/delete`,
                    {
                      headers: {
                        Authorization: this.currentUser.token,
                      },
                    }, // 添加token到请求头
                    console.log(this.currentUser.token)
                )
                .then((res) => {
                  if (res.data.code === "0") {
                    msg("success", "删除成功");
                    this.loadTable(this.pageInfo.pageNum); // 重新加载当前页
                  } else {
                    msg("error", res.data.msg || "删除失败");
                  }
                })
                .catch((error) => {
                  console.error("删除失败:", error);
                  msg("error", "删除失败：" + error.message);
                });
          })
          .catch(() => {});
    },

    viewDetail(postId) {
      this.showPostDetail = true;
      axios
          .get(`https://scutdionysus.cn/api/posts/${postId}`)
          .then((res) => {
            if (res.data.code === "0") {
              const postData = res.data.data;

              // 不需要预处理JSON字符串，直接保存原始数据
              this.selectedPost = postData;
              msg("success", "加载博文详情成功");
            } else {
              msg("error", res.data.msg || "获取博文详情失败");
            }
          })
          .catch((error) => {
            console.error("加载博文详情失败:", error);
            msg("error", "加载失败：" + error.message);
          });
    },

    backToList() {
      this.showPostDetail = false;
      this.selectedPost = {};

      // 清除URL中的postId参数并刷新页面
      const url = new URL(window.location.href);
      url.searchParams.delete("postId");
      window.history.replaceState({}, "", url.toString());
    },

    getAuthorAvatarUrl(avatarJson) {
      const defaultAvatar = "../../file/img/userCover.png";
      if (!avatarJson) {
        return defaultAvatar;
      }

      try {
        const avatar = JSON.parse(avatarJson);
        return avatar && avatar.id
            ? `https://scutdionysus.cn/api/files/${avatar.id}/download`
            : defaultAvatar;
      } catch (e) {
        console.error("解析头像数据失败:", e);
        return defaultAvatar;
      }
    },

    previewImage(imageJson) {
      if (!imageJson) return;

      try {
        const imageUrl = this.getPostImageUrl(imageJson);
        if (imageUrl) {
          this.previewImageUrl = imageUrl;
          this.previewDialogVisible = true;
        }
      } catch (e) {
        console.error("预览图片失败:", e);
        msg("error", "图片预览失败");
      }
    },
  },
});
