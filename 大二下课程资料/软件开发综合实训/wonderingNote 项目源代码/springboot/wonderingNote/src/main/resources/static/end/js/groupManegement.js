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
      teamName: "",
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
    preActive: true,
    nextActive: true,
    showTeamDetail: false,
    selectedTeam: {},
    teamMembers: [],
    currentTab: "members",
    teamChallenges: [],
    challengesLoading: false,
    challengesLastCursor: 0,
    hasMoreChallenges: true,
    membersLoading: false,
    membersLastCursor: 0,
    hasMoreMembers: true,
    membersSize: 20,
    challengePageInfo: {
      pageNum: 1,
      pageSize: 10,
      total: 0,
      hasNextPage: false,
    },
    dialogVisible: false,
    previewImageUrl: "",
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
    this.loadTable(1);
  },
  methods: {
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

    loadTable(pageNum) {
      const params = {
        pageNum: pageNum || this.pageInfo.pageNum || 1,
        pageSize: this.pageInfo.pageSize || 10,
        name: this.info4Search.teamName || "",
        startTime: this.formatDateTime(this.info4Search.startTime) || "",
        endTime: this.formatDateTime(this.info4Search.endTime) || "",
      };

      const queryParams = new URLSearchParams(params);
      const url = `https://scutdionysus.cn/api/admin/team/search?${queryParams.toString()}`;

      axios
          .get(url)
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
        pageSize: this.pageInfo.pageSize,
        total: data.total || 0,
        hasNextPage: data.hasNextPage || false,
      };
      this.preActive = this.pageInfo.pageNum <= 1;
      this.nextActive = !this.pageInfo.hasNextPage;
    },

    searchTeams() {
      this.loadTable(1);
    },

    viewDetail(teamId) {
      this.showTeamDetail = true;
      this.currentTab = "members"; // 默认显示成员列表

      const fullUrl = `https://scutdionysus.cn/api/teams/${teamId}/info`;
      console.log("请求的完整URL:", fullUrl);
      // 获取团队详细信息
      axios
          .get(`https://scutdionysus.cn/api/teams/${teamId}/info`)
          .then((res) => {
            if (res.data.code === "0") {
              this.selectedTeam = {
                ...res.data.data,
                teamId: teamId,
              };
              // logo数据会在模板中通过getTeamLogoUrl方法处理
              this.loadTeamMembers(teamId);
              console.log("团队信息:", this.selectedTeam);
              msg("success", "获取团队信息成功");
            } else {
              msg("error", res.data.msg || "获取团队信息失败");
            }
          })
          .catch((error) => {
            console.error("获取团队信息失败:", error);
            msg("error", "获取团队信息失败：" + error.message);
          });
    },

    getMemberAvatarUrl(avatar) {
      const defaultAvatar = "../../file/img/userCover.png";
      if (!avatar) {
        return defaultAvatar;
      }

      try {
        const avatarData = JSON.parse(avatar);
        return avatarData && avatarData.id
            ? `https://scutdionysus.cn/api/files/${avatarData.id}/download`
            : defaultAvatar;
      } catch (e) {
        console.error("解析用户头像数据失败:", e);
        return defaultAvatar;
      }
    },

    loadTeamMembers(teamId, isLoadMore = false) {
      if (!isLoadMore) {
        this.teamMembers = [];
        this.membersLastCursor = 0;
        this.hasMoreMembers = true;
      }

      if (!this.hasMoreMembers || this.membersLoading) {
        return;
      }

      this.membersLoading = true;

      axios
          .get(`https://scutdionysus.cn/api/teams/${teamId}/members`, {
            params: {
              size: this.membersSize,
              lastCursor: this.membersLastCursor,
            },
          })
          .then((res) => {
            if (res.data.code === "0") {
              const newMembers = res.data.data.data.map((member) => ({
                ...member,
                user_avatar: member.user_avatar || null, // 确保空值时设为 null
              }));
              this.teamMembers = [...this.teamMembers, ...newMembers];

              // 更新lastCursor值
              this.membersLastCursor = res.data.data.nextCursor;
              this.hasMoreMembers = this.membersLastCursor !== null;

              if (!isLoadMore) {
                msg("success", "加载成员列表成功");
              }
            } else {
              msg("error", res.data.msg || "获取团队成员失败");
            }
          })
          .catch((error) => {
            console.error("获取团队成员失败:", error);
            msg("error", "获取团队成员失败：" + error.message);
          })
          .finally(() => {
            this.membersLoading = false;
          });
    },

    loadTeamChallenges(teamId, pageNum = 1) {
      if (this.challengesLoading) return;

      // 添加平滑滚动到列表顶部
      const listElement = document.querySelector(".challenge-list");
      if (listElement) {
        listElement.scrollIntoView({
          behavior: "smooth",
          block: "start",
        });
      }

      this.challengesLoading = true;
      const params = {
        pageNum: pageNum,
        pageSize: 2, // 修改为每页显示2条数据
      };

      const queryParams = new URLSearchParams(params);
      axios
          .get(
              `https://scutdionysus.cn/api/admin/team/${teamId}?${queryParams.toString()}`
          )
          .then((res) => {
            if (res.data.code === "0") {
              this.teamChallenges = res.data.data.list;
              // 更新分页信息
              this.challengePageInfo = {
                pageNum: res.data.data.pageNum,
                pageSize: res.data.data.pageSize,
                total: res.data.data.total,
                hasNextPage: res.data.data.hasNextPage,
              };
              msg("success", "获取团队挑战成功");
            } else {
              msg("error", res.data.msg || "获取团队挑战失败");
            }
          })
          .catch((error) => {
            console.error("获取团队挑战失败:", error);
            msg("error", "获取团队挑战失败：" + error.message);
          })
          .finally(() => {
            this.challengesLoading = false;
          });
    },

    viewChallengeDetail(challengeId) {
      // 跳转到挑战详情页面，并携带挑战ID参数
      location.href = `challenge.html?challengeId=${challengeId}`;
    },

    handleScroll(e) {
      if (this.currentTab === "members") {
        const element = e.target;
        if (
            element.scrollHeight - element.scrollTop - element.clientHeight <
            100
        ) {
          this.loadTeamMembers(this.selectedTeam.teamId, true);
        }
      }
    },

    switchTab(tab) {
      this.currentTab = tab;
      const teamId = this.selectedTeam.teamId;

      if (tab === "members") {
        // 重置成员列表状态
        this.teamMembers = [];
        this.membersLastCursor = 0;
        this.hasMoreMembers = true;
        this.loadTeamMembers(this.selectedTeam.teamId, false);
      } else if (tab === "challenges") {
        // 重置挑战列表分页信息
        this.challengePageInfo.pageNum = 1;
        this.loadTeamChallenges(teamId);
      }
    },

    backToList() {
      this.showTeamDetail = false;
      this.selectedTeam = {};
      this.teamMembers = [];
      this.teamChallenges = [];
      this.currentTab = "members";
    },

    viewUserDetail(userId) {
      // 使用 URL 参数传递用户 ID 并跳转
      location.href = `userManagement.html?userId=${userId}`;
    },

    previewImage(team) {
      const defaultLogo = "../../file/img/userCover.png";
      if (!team.logo) {
        this.previewImageUrl = defaultLogo;
        this.dialogVisible = true;
        return;
      }

      try {
        const logoData = JSON.parse(team.logo);
        this.previewImageUrl =
            logoData && logoData.id
                ? `https://scutdionysus.cn/api/files/${logoData.id}/download`
                : defaultLogo;
        this.dialogVisible = true;
      } catch (e) {
        console.error("解析团队logo数据失败:", e);
        this.previewImageUrl = defaultLogo;
        this.dialogVisible = true;
      }
    },

    getTeamLogoUrl(logo) {
      const defaultLogo = "../../file/img/userCover.png";
      if (!logo) {
        return defaultLogo;
      }

      try {
        const logoData = JSON.parse(logo);
        return logoData && logoData.id
            ? `https://scutdionysus.cn/api/files/${logoData.id}/download`
            : defaultLogo;
      } catch (e) {
        console.error("解析团队logo数据失败:", e);
        return defaultLogo;
      }
    },
  },
});
