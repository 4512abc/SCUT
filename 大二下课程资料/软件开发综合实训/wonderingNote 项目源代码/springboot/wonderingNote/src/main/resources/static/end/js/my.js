function checkValid(entity) {
  if (!entity.name || entity.name.trim() === "") {
    alert("姓名不能为空");
    return false;
  }

  let phone = String(entity.phone).trim();
  if (!phone) {
    alert("手机号不能为空");
    return false;
  }

  let reg = /^1[3456789]\d{9}$/;
  if (!reg.test(phone)) {
    alert("请输入有效的中国大陆手机号");
    return false;
  }

  if (entity.email && entity.email.trim() !== "") {
    let emailReg = /^([a-zA-Z0-9_\-\.]+)@([a-zA-Z0-9_\-\.]+)\.([a-zA-Z]{2,5})$/;
    if (!emailReg.test(entity.email)) {
      alert("请输入正确的邮箱");
      return false;
    }
  }

  if (entity.cardId && entity.cardId.trim() !== "") {
    let cardReg = /(^\d{15}$)|(^\d{18$)|(^\d{17}(\d|X|x)$)/;
    if (!cardReg.test(entity.cardId)) {
      alert("请输入正确的身份证号");
      return false;
    }
  }

  return true;
}

function personalPage() {
  let user = JSON.parse(localStorage.getItem("user"));
  if (user && user.level && user.level === 1) {
    window.location = "../page/accountUserInfo.html";
  }
  if (user && user.level && user.level === 2) {
    window.location = "../page/accountTeacherInfo.html";
  }
  if (user && user.level && user.level === 3) {
    window.location = "../page/accountStudentInfo.html";
  }
}

function goToPage(page) {
  window.location.href = page + ".html";
}

/**
 * 弹出式提示框，默认1.2秒自动消失
 * @param message 提示信息
 * @param style 提示样式，有alert-success、alert-danger、alert-warning、alert-info
 * @param time 消失时间
 */
let prompt = function (message, style, time) {
  style = style === undefined ? "alert-success" : style;
  time = time === undefined ? 1200 : time;
  $("<div>")
    .appendTo("body")
    .addClass("alert " + style)
    .html(message)
    .show()
    .delay(time)
    .fadeOut();
};

// 成功提示
let success_prompt = function (message, time) {
  prompt(message, "alert-success", time);
};

// 失败提示
let fail_prompt = function (message, time) {
  prompt(message, "alert-danger", time);
};

// 提醒
let warning_prompt = function (message, time) {
  prompt(message, "alert-warning", time);
};

// 信息提示
let info_prompt = function (message, time) {
  prompt(message, "alert-info", time);
};

function logout() {
  // 先清除用户信息
  localStorage.removeItem("currentUser");

  // 清空历史记录
  window.history.replaceState(null, "", "login.html");
  window.history.pushState(null, "", "login.html");

  // 跳转到登录页
  window.location.href = "login.html";
}

// 验证是否已登录
function checkLogin() {
  const currentUser = localStorage.getItem("currentUser");
  if (!currentUser) {
    // 未登录，重定向到登录页面
    window.location.replace("login.html");
    return false;
  }
  return true;
}

// 检查登录页和注册页是否已登录
function checkLoginStatus() {
  const currentUser = localStorage.getItem("currentUser");
  if (currentUser) {
    // 已登录，重定向到主页
    window.location.replace("main.html");
  }
}
