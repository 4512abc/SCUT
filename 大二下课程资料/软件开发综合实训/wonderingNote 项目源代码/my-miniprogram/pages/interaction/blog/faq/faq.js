// faq.js
Page({
  data: {
    faqs: [
      {
        icon: "/images/icon-notebook.jpg",
        question: "1.游记是只有自己可见吗？",
        answer: "可选择公开或私密！"
      },
      {
        icon: "/images/icon-yellow-block.jpg",
        question: "2.数据会丢失吗？",
        answer: "放心鸥，数据是云端存储哒，我们是不会删除用户数据的。数据具有安全性，不会强制用户上传人脸数据，只有加入群体用户才有权上传人脸！！！"
      },
      {
        icon: "/images/icon-computer.jpg",
        question: "3.电脑端是否可以使用",
        answer: "可以，安装微信电脑客户端，打开小程序即可"
      },
      {
        icon: "/images/icon-notice.jpg",
        question: "4.注意事项",
        answer: "本小程序为工具类软件，专注于提供用户'写游记，参加挑战'等相关功能。严禁用户借助本软件发布、传播任何违法、违规内容，若发现违规、违法行为，将立即采取限制使用等措施。"
      },
      {
        icon: "/images/icon-security.jpg",
        question: "5.关于内容鉴别措施",
        answer: "本小程序已接入微信图文风控系统，对文本和图片内容进行自动检测。对于检测出的违规、违法内容，将根据平台规定采取限制使用或其他相应处理措施，以保障平台内容合规、安全。"
      }
    ]
  },

  onLoad() {
    this.getSystemInfo();

    const savedTheme = wx.getStorageSync('theme') || 0;
    this.setTheme(savedTheme);
  },

  getSystemInfo() {
    const systemInfo = wx.getSystemInfoSync();
    this.setData({
      statusBarHeight: systemInfo.statusBarHeight
    });
  },

  onClickLeft() {
    wx.navigateBack();
  }
})