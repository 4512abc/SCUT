let wrapper = new Vue({
  // 修改这里，添加new关键字
  el: "#app",
  data: {
    user: {
      account: "",
      loginType: "username",
      password: "",
    },
  },
  created: function () {
    this.resetForm();
    // 添加强制登录检查
    this.checkLoginStatus();
  },
  methods: {
    checkLoginStatus() {
      window.checkLoginStatus(); // 使用全局函数检查登录状态
    },
    resetForm() {
      this.user.account = "";
      this.user.loginType = "";
      this.user.password = "";
    },
    goToPage(page) {
      window.goToPage(page); // 修改这里，使用window全局对象调用my.js中的函数
    },
    login() {
      if (!this.user.password || !this.user.loginType || !this.user.account) {
        alert("请输入用户信息");
        return;
      }
      axios
        .post("https://scutdionysus.cn/api/admin/login", this.user)
        .then((res) => {
          if (res.data.code === "0") {
            // 这里的对象是 后端返回的信息，现在登录的账号
            localStorage.setItem("currentUser", JSON.stringify(res.data.data));
            /*res.data.data 包含：
                            id: 用户id
                            account: 用户名
                            email: 邮箱
                            accessLevel:  权限等级
                            status: 账号状态
                            其他与用户相关的数据*/
            location.href = "main.html";
          } else {
            alert(res.data.msg);
          }
        });
    },
  },
});
