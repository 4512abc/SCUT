// 返回数据加载结果提示框
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
    isSuperAdmin: false,
    info4Search: {
      accessLevel: "user", // 默认为user
      userAccount: "",
      status: "ACTIVE", // 默认为活跃
      email: "", // 邮箱
      startTime: "", // 开始时间
      endTime: "", // 结束时间
    },
    searchKeyword: "", // 搜索关键字
    objs: [],
    pageInfo: {
      pageNum: 1,
      pageSize: 10, // 设置默认每页显示数量
      total: 0,
      hasNextPage: false,
    },
    preActive: false,
    nextActive: false,
    showUserDetail: false,
    selectedUser: {},
    userPosts: [],
    currentTab: "posts",
    tabs: [
      { key: "posts", name: "博文列表" },
      { key: "comments", name: "评论列表" },
      { key: "challenges", name: "挑战列表" },
    ],
    selectedUser: {},
    userComments: [],
    userChallenges: [],
    postsLoading: false,
    postsLastCursor: 0,
    hasMorePosts: true,
    postsSize: 30,
    challengesLoading: false,
    challengesLastCursor: 0,
    hasMoreChallenges: true,
    challengesSize: 10,
    commentsLoading: false,
    commentsLastCursor: 0,
    hasMoreComments: true,
    commentsSize: 10,
    userData: {
      likeCount: 0,
      commentCount: 0,
    },
    dialogVisible: false,
    previewImageUrl: "",
  },
  created: function () {
    if (!window.checkLogin()) return; // 添加登录验证
    try {
      const currentUser = localStorage.getItem("currentUser");
      this.currentUser = currentUser ? JSON.parse(currentUser) : {};

      // 检查当前用户是否为超级管理员
      this.isSuperAdmin =
          this.currentUser?.userInfo?.access_level === "super_admin";

      // 如果不是超级管理员且当前选择的是admin，则强制设置为user
      if (!this.isSuperAdmin && this.info4Search.accessLevel === "admin") {
        this.info4Search.accessLevel = "user";
      }

      // 获取 URL 参数中的 userId
      const urlParams = new URLSearchParams(window.location.search);
      const userId = urlParams.get("userId");

      if (userId) {
        this.viewUserDetail(userId);
      }
    } catch (e) {
      this.currentUser = {};
      this.isSuperAdmin = false;
      console.error("用户信息解析失败:", e);
    }
    this.loadTable(1);
  },

  methods: {
    pickFromKey: function (obj, startKey) {
      let start = false;
      return Object.entries(obj).reduce((result, [key, value]) => {
        if (key === startKey) start = true;
        if (start) result[key] = value;
        return result;
      }, {});
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

    loadTable: function (pageNum) {
      // 构造基础参数
      const params = {
        pageNum: pageNum || this.pageInfo.pageNum || 1,
        pageSize: this.pageInfo.pageSize || 10,
        accessLevel: this.info4Search.accessLevel,
        status: this.info4Search.status,
        startTime: this.formatDateTime(this.info4Search.startTime) || "",
        endTime: this.formatDateTime(this.info4Search.endTime) || "",
      };

      // 处理搜索关键字
      if (this.searchKeyword) {
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (emailRegex.test(this.searchKeyword)) {
          params.email = this.searchKeyword;
          params.userAccount = "";
        } else {
          params.userAccount = this.searchKeyword;
          params.email = "";
        }
      } else {
        params.email = "";
        params.userAccount = "";
      }

      const queryParams = new URLSearchParams(params);
      const fullUrl = `https://scutdionysus.cn/api/admin/users/search?${queryParams.toString()}`;

      axios
          .get(fullUrl)
          .then((res) => {
            if (res.data.code === "0") {
              this.objs = res.data.data.list;
              this.updatePageInfo(res.data.data);
              console.log(this.objs);
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

    // 添加新的模糊搜索函数
    // 添加邮箱验证函数
    isEmail(value) {
      const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
      return emailRegex.test(value);
    },

    searchUsers() {
      this.loadTable(1); // 直接调用loadTable并重置到第一页
    },
    setUserState(userId, state) {
      const actionText = state === "ACTIVE" ? "解冻" : "冻结";
      this.$confirm(`确认${actionText}该用户?`, "提示", {
        confirmButtonText: "确定",
        cancelButtonText: "取消",
        type: "warning",
      })
          .then(() => {
            const data = {
              user_state: state,
            };

            axios
                .post(
                    `https://scutdionysus.cn/api/admin/users/${userId}/set_state`,
                    data,
                    {
                      headers: {
                        "Content-Type": "application/json",
                      },
                    }
                )
                .then((res) => {
                  if (res.data.code === "0") {
                    msg("success", `${actionText}成功`);
                    this.loadTable(this.pageInfo.pageNum); // 重新加载当前页数据
                  } else {
                    msg("error", res.data.msg || `${actionText}失败`);
                  }
                })
                .catch((error) => {
                  console.error(`${actionText}失败:`, error);
                  msg("error", `${actionText}失败：` + error.message);
                });
          })
          .catch(() => {});
    },
    viewUserDetail(userId) {
      this.showUserDetail = true;
      this.currentTab = "posts"; // 默认显示博文列表

      // 获取用户详细信息
      Promise.all([
        axios.get(`https://scutdionysus.cn/api/users/${userId}`),
        axios.get(`https://scutdionysus.cn/api/admin/users/${userId}/data`),
      ])
          .then(([userRes, dataRes]) => {
            if (userRes.data.code === "0" && dataRes.data.code === "0") {
              this.selectedUser = userRes.data.data;
              this.selectedUser.userId = userId;
              this.userData = dataRes.data.data;
              this.loadUserPosts(userId);
              msg("success", "获取用户信息成功");
            } else {
              msg("error", "获取用户信息失败");
            }
          })
          .catch((error) => {
            console.error("获取用户信息失败:", error);
            msg("error", "获取用户信息失败：" + error.message);
          });
    },

    switchTab(tab) {
      this.currentTab = tab;
      const userId = this.selectedUser.userId;

      if (tab === "posts") {
        // 重置博文列表状态
        this.userPosts = [];
        this.postsLastCursor = 0;
        this.hasMorePosts = true;
        this.loadUserPosts(userId, false);
      } else if (tab === "comments") {
        this.loadUserComments(userId);
      } else if (tab === "challenges") {
        this.loadUserChallenges(userId);
      }
    },
    loadUserPosts(userId, isLoadMore = false) {
      if (!isLoadMore) {
        this.userPosts = [];
        this.postsLastCursor = 0;
        this.hasMorePosts = true;
      }

      if (!this.hasMorePosts || this.postsLoading) {
        return;
      }

      this.postsLoading = true;

      axios
          .get(`https://scutdionysus.cn/api/users/${userId}/posts`, {
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
              this.userPosts = [...this.userPosts, ...newPosts];

              // 更新lastCursor值
              this.postsLastCursor = res.data.data.nextCursor;
              console.log("更新后的lastCursor:", this.postsLastCursor);
              // 如果返回的lastCursor为null，说明没有更多数据了
              this.hasMorePosts = this.postsLastCursor !== null;
              msg("success", `加载成功，当前博文数量：${this.userPosts.length}`);
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

    handleScroll(e) {
      if (this.currentTab === "posts") {
        // ...existing posts scroll code...
        const element = e.target;
        // 当滚动到距离底部100px时触发加载
        if (
            element.scrollHeight - element.scrollTop - element.clientHeight <
            100
        ) {
          this.loadUserPosts(this.selectedUser.userId, true);
        }
      } else if (this.currentTab === "challenges") {
        const element = e.target;
        if (
            element.scrollHeight - element.scrollTop - element.clientHeight <
            100
        ) {
          this.loadUserChallenges(this.selectedUser.userId, true);
        }
      } else if (this.currentTab === "comments") {
        const element = e.target;
        if (
            element.scrollHeight - element.scrollTop - element.clientHeight <
            100
        ) {
          this.loadUserComments(this.selectedUser.userId, true);
        }
      }
    },

    loadUserComments(userId, isLoadMore = false) {
      if (!isLoadMore) {
        this.userComments = [];
        this.commentsLastCursor = 0;
        this.hasMoreComments = true;
      }

      if (!this.hasMoreComments || this.commentsLoading) {
        return;
      }

      this.commentsLoading = true;

      axios
          .get(`https://scutdionysus.cn/api/admin/users/${userId}/user_info`, {
            params: {
              size: this.commentsSize,
              lastCursor: this.commentsLastCursor,
            },
          })
          .then((res) => {
            if (res.data.code === "0") {
              const newComments = res.data.data.data;
              this.userComments = [...this.userComments, ...newComments];

              // 更新lastCursor值
              this.commentsLastCursor = res.data.data.nextCursor;
              // 如果返回的lastCursor为null，说明没有更多数据了
              this.hasMoreComments = this.commentsLastCursor !== null;
              msg(
                  "success",
                  `加载成功，当前评论数量：${this.userComments.length}`
              );
            } else {
              msg("error", res.data.msg || "获取评论列表失败");
            }
          })
          .catch((error) => {
            console.error("加载评论失败:", error);
            msg("error", "加载评论失败：" + error.message);
          })
          .finally(() => {
            this.commentsLoading = false;
          });
    },

    loadUserChallenges(userId, isLoadMore = false) {
      if (!isLoadMore) {
        this.userChallenges = [];
        this.challengesLastCursor = 0;
        this.hasMoreChallenges = true;
      }

      if (!this.hasMoreChallenges || this.challengesLoading) {
        return;
      }

      this.challengesLoading = true;

      axios
          .get(`https://scutdionysus.cn/api/users/${userId}/challenges`, {
            params: {
              size: this.challengesSize,
              lastCursor: this.challengesLastCursor,
              sort: "id",
            },
          })
          .then((res) => {
            if (res.data.code === "0") {
              const newChallenges = res.data.data.data;
              this.userChallenges = [...this.userChallenges, ...newChallenges];

              // 更新lastCursor值
              this.challengesLastCursor = res.data.data.nextCursor;
              // 如果返回的lastCursor为null，说明没有更多数据了
              this.hasMoreChallenges = this.challengesLastCursor !== null;
              msg(
                  "success",
                  `加载成功，当前挑战数量：${this.userChallenges.length}`
              );
            } else {
              msg("error", res.data.msg || "获取挑战列表失败");
            }
          })
          .catch((error) => {
            console.error("加载挑战失败:", error);
            msg("error", "加载挑战失败：" + error.message);
          })
          .finally(() => {
            this.challengesLoading = false;
          });
    },

    backToList() {
      this.showUserDetail = false;
      this.selectedUser = {};
      this.userPosts = [];

      // 清除URL中的userId参数
      const url = new URL(window.location.href);
      url.searchParams.delete("userId");
      window.history.replaceState({}, "", url.toString());
    },

    viewPostDetail(postId) {
      // 使用 URL 参数传递博文 ID
      location.href = `blog.html?postId=${postId}`;
    },

    viewChallengeDetail(challengeId) {
      location.href = `challenge.html?challengeId=${challengeId}`;
    },
    previewImage(obj) {
      if (!obj.avatar) {
        this.previewImageUrl = "../../file/img/userCover.png";
        this.dialogVisible = true;
        return;
      }

      try {
        const avatarData = JSON.parse(obj.avatar);
        if (avatarData && avatarData.id) {
          this.previewImageUrl = `https://scutdionysus.cn/api/files/${avatarData.id}/download`;
        } else {
          this.previewImageUrl = "../../file/img/userCover.png";
        }
        this.dialogVisible = true;
      } catch (e) {
        console.error("解析头像数据失败:", e);
        this.previewImageUrl = "../../file/img/userCover.png";
        this.dialogVisible = true;
      }
    },
    getUserAvatarUrl(avatarData) {
      if (!avatarData) {
        return "../../file/img/userCover.png";
      }
      try {
        const parsed = JSON.parse(avatarData);
        if (parsed && parsed.id) {
          return `https://scutdionysus.cn/api/files/${parsed.id}/download`;
        }
      } catch (e) {
        console.error("解析头像数据失败:", e);
      }
      return "../../file/img/userCover.png";
    },
  },
});
