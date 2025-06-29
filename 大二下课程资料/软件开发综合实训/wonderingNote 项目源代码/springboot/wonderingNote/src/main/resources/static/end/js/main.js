new Vue({
  el: "#wrapper",
  data: {
    currentUser: {},
    sysData: null, // 用于存储系统数据
    challengeData: null, // 新增：用于存储挑战等级数据
    announcementData: null, // 新增：用于存储公告数据
    chartXData: [], // 新增：图表 x 轴数据
    postCountData: [], // 新增：帖子数量数据
    challengeCountData: [], // 新增：挑战数量数据
    chart: null, // 新增：图表实例
    dialogVisible: false,
    previewImageUrl: "",
  },
  created: function () {
    if (!window.checkLogin()) return; // 添加登录验证
    try {
      const userStr = localStorage.getItem("currentUser");
      this.currentUser = userStr ? JSON.parse(userStr) : {};
    } catch (e) {
      this.currentUser = {};
      console.error("用户信息解析失败:", e);
    }
    // 发起原有接口请求
    axios
      .get("https://scutdionysus.cn/api/admin/top_page/Sys_number")
      .then((response) => {
        if (response.data.code === "0") {
          this.sysData = response.data.data;
        }
      })
      .catch((error) => {
        console.error("获取系统数据失败:", error);
      });
    // 新增：发起挑战等级接口请求
    axios
      .get("https://scutdionysus.cn/api/admin/top_page/challenge_level")
      .then((response) => {
        if (response.data.code === "0") {
          this.challengeData = response.data.data;
        }
      })
      .catch((error) => {
        console.error("获取挑战等级数据失败:", error);
      });
    // 新增：发起公告接口请求
    axios
      .get("https://scutdionysus.cn/api/admin/top_page/announcement_data")
      .then((response) => {
        if (response.data.code === "0") {
          this.announcementData = response.data.data;
        }
      })
      .catch((error) => {
        console.error("获取公告数据失败:", error);
      });
    // 新增：发起挑战数据接口请求
    axios
      .get("https://scutdionysus.cn/api/admin/top_page/challenge_data")
      .then((response) => {
        if (response.data.code === "0") {
          const data = response.data.data;
          // 对月份进行排序
          const sortedData = data.sort((a, b) => {
            // 将月份转换为可比较的格式 (YYYY-MM)
            return a.month.localeCompare(b.month);
          });

          this.chartXData = sortedData.map((item) => item.month);
          this.postCountData = sortedData.map((item) => item.post_count);
          this.challengeCountData = sortedData.map(
            (item) => item.challenge_count
          );

          if (this.chart) {
            this.chart.setOption({
              xAxis: {
                data: this.chartXData,
                axisLabel: {
                  rotate: 45, // 斜着显示文字，防止重叠
                },
              },
              series: [
                { name: "帖子数量", data: this.postCountData },
                { name: "挑战数量", data: this.challengeCountData },
              ],
            });
          }
        }
      })
      .catch((error) => {
        console.error("获取挑战数据失败:", error);
      });
  },
  // 在 methods 中添加时间格式化方法
  methods: {
    getAvatarUrl(avatar) {
      if (!avatar) {
        return "../../file/img/userCover.png"; // 默认头像
      }
      try {
        const avatarObj = JSON.parse(avatar);
        return `https://scutdionysus.cn/api/files/${avatarObj.id}/download`;
      } catch (e) {
        console.error("解析头像数据失败:", e);
        return "../../file/img/userCover.png";
      }
    },
    // 新增时间格式化方法
    formatTime(time) {
      if (!time) {
        return "";
      }
      const date = new Date(time);
      // 检查是否是有效的日期
      if (isNaN(date.getTime())) {
        return "无效日期";
      }
      const year = date.getFullYear();
      const month = String(date.getMonth() + 1).padStart(2, "0");
      const day = String(date.getDate()).padStart(2, "0");
      const hours = String(date.getHours()).padStart(2, "0");
      const minutes = String(date.getMinutes()).padStart(2, "0");
      return `${year}-${month}-${day} ${hours}:${minutes}`;
    },
    goToMain() {
      location.href = "/end/page/main.html";
    },
    goToUserManagement() {
      location.href = "/end/page/userManagement.html";
    },
    goToPersonal() {
      location.href = "/end/page/personal.html";
    },
    previewImage(url) {
      this.previewImageUrl = url;
      this.dialogVisible = true;
    },
    logout() {
      window.logout(); // 使用全局logout函数
    },
  },
  mounted: function () {
    this.chart = echarts.init(document.getElementById("lineChart"));
    const option = {
      title: {
        text: "博文与挑战数量统计",
        left: "center",
      },
      tooltip: {
        trigger: "axis",
        formatter: function (params) {
          let result = params[0].axisValue + "<br/>";
          params.forEach((item) => {
            result += `${item.seriesName}: ${item.value}<br/>`;
          });
          return result;
        },
      },
      legend: {
        data: ["帖子数量", "挑战数量"],
        bottom: "0",
      },
      grid: {
        left: "3%",
        right: "4%",
        bottom: "15%",
        top: "15%",
        containLabel: true,
      },
      xAxis: {
        type: "category",
        name: "月份",
        axisLabel: {
          rotate: 45,
        },
      },
      yAxis: {
        type: "value",
        name: "数量",
      },
      series: [
        {
          name: "帖子数量",
          data: this.postCountData,
          type: "line",
          smooth: true,
          itemStyle: {
            color: "#409EFF",
          },
        },
        {
          name: "挑战数量",
          data: this.challengeCountData,
          type: "line",
          smooth: true,
          itemStyle: {
            color: "#67C23A",
          },
        },
      ],
    };
    this.chart.setOption(option);
  },
});
