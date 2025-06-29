let wrapper = new Vue({
  el: "#app", // 这里vue一定要绑定对才有反应兄弟，匹配上面的div id = app
  data: {
    user: {
      email: "", // 邮箱
      code: "", // 验证码
      password: "", // 密码
    },
    countdown: 60,
    isCounting: false,
  },
  created: function () {
    this.resetForm();
    // 允许从登录页面返回
    history.pushState(null, null, document.URL);
    window.checkLoginStatus(); // 添加登录状态检查
  },
  methods: {
    resetForm() {
      this.user.email = "";
      this.user.code = "";
      this.user.password = "";
      this.countdown = 60;
      this.isCounting = false;
    },
    goToLogin() {
      window.location.href = "login.html";
    },
    Register() {
      if (!this.user.email || !this.user.code || !this.user.password) {
        alert("请输入用户信息");
        return;
      }
      axios
        .post("https://scutdionysus.cn/api/admin/register", this.user)
        .then((res) => {
          if (res.data.code === "0") {
            alert("注册成功");
            location.href = "login.html";
          } else {
            alert(res.data.msg);
          }
        });
    },
    getCode() {
      if (this.isCounting) {
        alert("请稍后再试");
        return;
      }
      if (!this.user.email) {
        alert("请输入邮箱");
        return;
      }
      axios
        .post("https://scutdionysus.cn/api/auth/email_code", {
          email: this.user.email,
        })
        .then((res) => {
          if (res.data.code === "0") {
            alert("验证码已发送");
            this.countdown = res.data.expire_in || 60;
            this.isCounting = true;

            let timer = setInterval(() => {
              this.countdown--;

              if (this.countdown <= 0) {
                clearInterval(timer);
                this.isCounting = false;
                this.countdown = 60;
              }
            }, 1000);
          } else {
            alert(res.data.msg);
          }
        });
    },
  },
});
