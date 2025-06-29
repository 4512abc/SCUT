function msg(type, msg) {
  Vue.prototype.$message({
    type: type,
    message: msg,
    duration: 2000,
    offset: 100,
    center: true,
  });
}
let quill;

let wrapper = new Vue({
  el: "#wrapper",
  data: {
    currentUser: {},
    name: "", // 要查询的名称
    objs: [], // 后台返回的是一个列表
    pageInfo: {},
    preActive: true, // 有上一页为false，没有上一页为true
    nextActive: true,
    entity: {
      title: "",
      content: "",
      type: 0, // 默认选中用户端
    }, // 用于新增或编辑的实体对象
    currentDate: new Date().toLocaleString(),
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
  },
  mounted() {
    // 添加mounted钩子
    this.initQuill();
  },
  methods: {
    initQuill() {
      quill = new Quill("#editor", {
        modules: {
          toolbar: {
            container: [
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
        },
        theme: "snow",
        placeholder: "请输入公告内容...",
        bounds: "#editor",
      });

      // 设置初始内容
      if (this.entity.content) {
        quill.root.innerHTML = this.entity.content;
      }

      // 监听内容变化
      quill.on("text-change", () => {
        this.entity.content = quill.root.innerHTML;
      });
    },
    /**
     * 加载表单
     * */
    loadTable(pageNum) {
      let name = this.name === "" ? "all" : this.name;
      axios
        .get("/announcementInfo/page/" + name + "?pageNum=" + pageNum)
        .then((res) => {
          if (res.data.code === "0") {
            this.objs = res.data.data.list;
            this.pageInfo = res.data.data;
            this.preActive = !this.pageInfo.hasPreviousPage;
            this.nextActive = !this.pageInfo.hasNextPage;
          } else {
            msg("error", res.data.msg);
          }
        });
    },
    submitAnnouncement() {
      // 数据验证
      if (!this.entity.title || typeof this.entity.title !== "string") {
        msg("error", "标题不能为空且必须是字符串");
        return;
      }
      if (!this.entity.content || typeof this.entity.content !== "string") {
        msg("error", "内容不能为空且必须是字符串");
        return;
      }

      const postData = {
        title: String(this.entity.title),
        content: String(quill.root.innerHTML),
        type: parseInt(this.entity.type),
      };

      // 新建公告
      axios
        .post(
          "https://scutdionysus.cn/api/admin/announcements/create",
          postData,
          {
            headers: {
              "Content-Type": "application/json",
              Authorization: this.currentUser.token, // 在headers中添加token
            },
          }
        )
        .then((res) => {
          if (res.data.code === "0") {
            msg("success", "发布成功");
          } else {
            msg("error", res.data.msg || "发布失败");
          }
        })
        .catch((error) => {
          msg("error", "发布失败：" + error.message);
        });
    },
  },
});

$("#saveBtn").click(function () {
  wrapper.submitAnnouncement();
});
