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
      startTime: "",
      endTime: "",
    },
    objs: [],
    pageInfo: {
      pageNum: 1,
      pageSize: 10,
    },
    preActive: false,
    nextActive: false,
    showDetail: false,
    showPostDetail: false,
    dialogVisible: false,
    previewImageUrl: "",
    selectedChallenge: {
      description: "",
      images: "",
      location: {
        lng: null,
        lat: null,
      },
      radius: 0,
      title: "",
      create_time: "",
      creator_id: null,
      end_time: "",
      gesture_type: "",
      object_type: "",
      start_time: "",
      team_id: null,
      landmark_name: "",
      need_face_verify: 0,
    },
  },
  created: function () {
    if (!window.checkLogin()) return; // 添加登录验证
    try {
      const currentUser = localStorage.getItem("currentUser");
      this.currentUser = currentUser ? JSON.parse(currentUser) : {};

      // 获取 URL 参数中的 challengeId
      const urlParams = new URLSearchParams(window.location.search);
      const challengeId = urlParams.get("challengeId");

      // 如果存在 challengeId，直接展示挑战详情
      if (challengeId) {
        // 构造一个临时对象，包含必要的 ID
        const tempChallenge = {
          challengeId: challengeId,
        };
        this.viewModal(tempChallenge);
      }
    } catch (e) {
      this.currentUser = {};
      console.error("用户信息解析失败:", e);
    }
    // 调用新接口
    this.loadTable(1);
  },
  methods: {
    formatDateTime(date) {
      if (!date) return "";
      // 将日期格式化为 YYYY-MM-DD HH:mm:ss
      return `${date} ${"00:00:00"}`;
    },

    loadTable: function (pageNum) {
      // 构造请求参数
      const params = {
        pageSize: this.pageInfo.pageSize || 10,
        pageNum: pageNum || this.pageInfo.pageNum || 1,
        title: this.info4Search.title || "",
        startTime: this.formatDateTime(this.info4Search.startTime) || "",
        endTime: this.formatDateTime(this.info4Search.endTime) || "",
      };

      // 构造查询字符串
      const queryString = new URLSearchParams(params).toString();

      // 使用axios.get发送请求
      axios
        .get(
          `https://scutdionysus.cn/api/admin/challenges/search?${queryString}`
        )
        .then((res) => {
          if (res.data.code === "0") {
            this.objs = res.data.data.list;
            this.updatePageInfo(res.data.data);
            console;
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

    searchChallenges() {
      this.loadTable(1);
    },

    del(id) {
      this.$confirm("确认删除该挑战?", "提示", {
        confirmButtonText: "确定",
        cancelButtonText: "取消",
        type: "warning",
      })
        .then(() => {
          axios
            .delete(`https://scutdionysus.cn/api/challenges/${id}/delete`, {
              headers: {
                Authorization: this.currentUser.token, // 增加token空值判断
              },
            })
            .then((res) => {
              if (res.data.code === "0") {
                msg("success", "删除成功");
                this.loadTable(this.pageInfo.pageNum);
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

    viewModal(challenge) {
      this.showDetail = true;
      this.selectedChallenge = challenge;

      axios
        .get(`https://scutdionysus.cn/api/challenges/${challenge.challengeId}`)
        .then((res) => {
          if (res.data.code === "0") {
            this.selectedChallenge = {
              ...this.selectedChallenge,
              ...res.data.data,
            };
            if (typeof this.selectedChallenge.images === "string") {
              try {
                this.selectedChallenge.images = JSON.parse(
                  this.selectedChallenge.images
                );
              } catch (e) {
                console.error("解析图片数据失败:", e);
              }
            }
          } else {
            msg("error", res.data.msg || "获取挑战详情失败");
          }
        })
        .catch((error) => {
          console.error("加载挑战详情失败:", error);
          msg("error", "加载失败：" + error.message);
        });
    },

    backToList() {
      this.showDetail = false;
      this.selectedChallenge = {};

      // 清除URL中的challengeId参数并刷新页面
      const url = new URL(window.location.href);
      url.searchParams.delete("challengeId");
      window.history.replaceState({}, "", url.toString());
    },

    previewImage(obj) {
      if (!obj.cover) {
        // 使用默认封面
        this.previewImageUrl = "../../file/img/challengeCover.png";
        this.dialogVisible = true;
        return;
      }

      try {
        const coverData = JSON.parse(obj.cover);
        if (Array.isArray(coverData) && coverData.length > 0) {
          this.previewImageUrl = `https://scutdionysus.cn/api/files/${coverData[0].id}/download`;
        } else {
          // 如果数据格式不正确，使用默认封面
          this.previewImageUrl = "../../file/img/challengeCover.png";
        }
        this.dialogVisible = true;
      } catch (e) {
        console.error("解析封面数据失败:", e);
        // 解析失败时使用默认封面
        this.previewImageUrl = "../../file/img/challengeCover.png";
        this.dialogVisible = true;
      }
    },

    // 在 methods 中添加获取图片URL的方法
    getChallengeImageUrl(images) {
      if (!images) {
        return "../../file/img/challengeCover.png"; // 默认封面
      }

      try {
        let imageData;
        // 判断是否已经是对象
        if (typeof images === "object") {
          imageData = images;
        } else {
          // 尝试解析JSON字符串
          imageData = JSON.parse(images);
        }

        if (imageData && imageData.id) {
          return `https://scutdionysus.cn/api/files/${imageData.id}/download`;
        }
        return "../../file/img/challengeCover.png";
      } catch (e) {
        console.error("解析图片数据失败:", e);
        return "../../file/img/challengeCover.png";
      }
    },
  },
});
