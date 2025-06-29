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
    userData: {
      base_info: {},
      profile_info: {},
      like_count: 0,
      comment_count: 0,
    },
    blogs: [],
    postsLoading: false,
    postsLastCursor: 0,
    hasMorePosts: true,
    postsSize: 10,
  },
  created: function () {
    if (!window.checkLogin()) return; // 添加登录验证
    try {
      const currentUser = localStorage.getItem("currentUser");
      this.currentUser = currentUser ? JSON.parse(currentUser) : {};
    } catch (e) {
      this.currentUser = {};
      console.error("用户信息解析失败:", e);
    }
    this.userData.id = this.currentUser.userInfo.id || null;
    console.log("当前用户信息:", this.userData.id);
    this.loadUserInfo();
  },
  methods: {
    setTab(tab) {
      this.currentTab = tab;
    },
    loadUserInfo() {
      Promise.all([
        axios.get("https://scutdionysus.cn/api/auth/home_info", {
          headers: {
            Authorization: this.currentUser.token,
          },
        }),
        axios.get(
          `https://scutdionysus.cn/api/admin/users/${this.currentUser.userInfo.id}/data`
        ),
      ])
        .then(([homeRes, dataRes]) => {
          if (homeRes.data.code === "0" && dataRes.data.code === "0") {
            const homeData = homeRes.data.data;
            const statsData = dataRes.data.data;

            // 更新userData
            this.userData = {
              ...this.userData,
              ...{
                account: homeData.base_info.account,
                avatar: homeData.base_info.avatar,
                email: homeData.base_info.email,
                gender: homeData.profile_info.gender,
                location: homeData.profile_info.location,
                bio: homeData.profile_info.bio,
                createTime: homeData.base_info.create_time,
                accessLevel: homeData.base_info.access_level,
                like_count: statsData.like_count || 0,
                comment_count: statsData.comment_count || 0,
              },
            };
            // 加载用户的博文
            this.loadUserPosts();
          }
        })
        .catch((error) => {
          console.error("获取用户信息失败:", error);
          msg("error", "获取用户信息失败：" + error.message);
        });
    },
    extractAvatarId(avatarJson) {
      try {
        const avatar = JSON.parse(avatarJson);
        return avatar.id;
      } catch (e) {
        return null;
      }
    },
    formatDate(dateStr) {
      if (!dateStr) return "";
      const date = new Date(dateStr);
      return date.toLocaleDateString("zh-CN", {
        year: "numeric",
        month: "long",
        day: "numeric",
        hour: "2-digit",
        minute: "2-digit",
      });
    },
    handleScroll(e) {
      const element = e.target;
      // 当滚动到距离底部100px时触发加载
      if (
        !this.postsLoading &&
        this.hasMorePosts &&
        element.scrollHeight - element.scrollTop - element.clientHeight < 100
      ) {
        console.log("触发滚动加载");
        this.loadUserPosts(true);
      }
    },

    loadUserPosts(isLoadMore = false) {
      if (!isLoadMore) {
        this.blogs = [];
        this.postsLastCursor = 0;
        this.hasMorePosts = true;
      }

      if (!this.hasMorePosts || this.postsLoading) {
        return;
      }

      this.postsLoading = true;
      console.log("开始加载博文，lastCursor:", this.postsLastCursor);

      axios
        .get(`https://scutdionysus.cn/api/users/${this.userData.id}/posts`, {
          params: {
            size: this.postsSize,
            sort: "id",
            lastCursor: this.postsLastCursor,
          },
        })
        .then((res) => {
          if (res.data.code === "0") {
            const newPosts = res.data.data.data;
            console.log("新加载的博文:", newPosts);
            this.blogs = [...this.blogs, ...newPosts];

            // 更新lastCursor值
            this.postsLastCursor = res.data.data.nextCursor;
            console.log("更新后的lastCursor:", this.postsLastCursor);
            this.hasMorePosts = this.postsLastCursor !== null;

            if (!isLoadMore) {
              msg("success", `加载成功，当前博文数量：${this.blogs.length}`);
            }
          } else {
            msg("error", res.data.msg || "获取博文列表失败");
          }
        })
        .catch((error) => {
          console.error("加载博文失败:", error);
          msg("error", "加载博文失败：" + error.message);
        })
        .finally(() => {
          this.postsLoading = false;
        });
    },

    viewPostDetail(postId) {
      // 使用 URL 参数传递博文 ID 并跳转
      location.href = `blog.html?postId=${postId}`;
    },

    mounted() {
      const mainContent = this.$el.querySelector(".profile-main");
      if (mainContent) {
        mainContent.addEventListener("scroll", this.handleScroll);
      }
    },
    beforeDestroy() {
      const mainContent = this.$el.querySelector(".profile-main");
      if (mainContent) {
        mainContent.removeEventListener("scroll", this.handleScroll);
      }
    },
  },
});
