// forget_password.js

const { apiDomain } = require("../../../config");
Page({
  data: {
    currentStep: 0,
    steps: [
      { title: '验证身份' },
      { title: '安全验证' },
      { title: '重置密码' }
    ],
    email: '',
    code: '',
    newPassword: '',
    confirmPassword: '',
    isSending: false,
    isVerifying: false,
    isResetting: false,
    sendBtnText: '发送验证码',
    countdown: 60,
    emailError: false,
    codeError: false,
    passwordError: false,
    confirmError: false
  },

  // 邮箱验证
  onEmailChange(e) {
    const email = e.detail;
    const emailRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;
    
    this.setData({
      email: email,
      emailError: email ? !emailRegex.test(email) : false // 只有当有输入时才显示错误
    });
  },
  
  validateEmail() {
    if (!this.data.email) {
      this.setData({ emailError: true });
      wx.showToast({
        title: '请输入邮箱',
        icon: 'none'
      });
      return false;
    }
    
    const emailRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;
    const isValid = emailRegex.test(this.data.email);
    
    if (!isValid) {
      this.setData({ emailError: true });
      wx.showToast({
        title: '邮箱格式不正确',
        icon: 'none'
      });
    }
    
    return isValid;
  },
  
  async sendVerificationCode() {
    if (!this.validateEmail()) return;
    if (this.data.isSending || this.data.sendBtnText !== '发送验证码' 
        && this.data.sendBtnText !== '重新发送') {
      return;
    }
  
    this.setData({ isSending: true });
    wx.showLoading({ title: '发送中...' });
  
    try {
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: 'https://' + apiDomain + '/api/auth/email_code',
          method: 'POST',
          data: { email: this.data.email },
          header: {
            'content-type': 'application/json'
          },
          success: (response) => {
            if (response.statusCode === 200) {
              resolve(response);
            } else {
              reject(new Error(response.data.msg || '发送失败'));
            }
          },
          fail: reject
        });
      });
  
      // 保存 sessionid
      if (res.header['Set-Cookie'] || res.header['set-cookie']) {
        wx.setStorageSync('sessionid', 
          res.header['Set-Cookie'] || res.header['set-cookie']);
      }
  
      this.startCountdown();
      wx.showToast({ title: '验证码已发送' });
      this.setData({ currentStep: 1 }); // 发送成功后进入下一步
  
    } catch (error) {
      wx.showToast({
        title: error.message || '发送失败',
        icon: 'none'
      });
      this.setData({
        isSending: false,
        sendBtnText: '重新发送'
      });
    } finally {
      wx.hideLoading();
    }
  },
  
  // 验证码输入处理
  onCodeChange(e) {
    this.setData({
      code: e.detail.substring(0, 6),
      codeError: false
    });
  },

  // 验证验证码
  async verifyCode() {
    if (!this.data.code || this.data.code.length !== 6) {
      this.setData({ codeError: true });
      wx.showToast({
        title: '请输入6位验证码',
        icon: 'none'
      });
      return;
    }

    this.setData({ isVerifying: true });
    wx.showLoading({ title: '验证中...' });

    try {
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: 'https://' + apiDomain + '/api/auth/verify_code',
          method: 'POST',
          data: {
            email: this.data.email,
            code: this.data.code
          },
          header: {
            'content-type': 'application/json',
            'Cookie': wx.getStorageSync('sessionid')
          },
          success: (response) => {
            if (response.statusCode === 200) {
              resolve(response);
            } else {
              reject(new Error(response.data.msg || '验证失败'));
            }
          },
          fail: reject
        });
      });

      // 验证成功，进入下一步
      this.setData({ 
        currentStep: 2,
        codeError: false 
      });
      
    } catch (error) {
      this.setData({ codeError: true });
      wx.showToast({
        title: error.message || '验证码错误',
        icon: 'none'
      });
    } finally {
      this.setData({ isVerifying: false });
      wx.hideLoading();
    }
  },

  startCountdown() {
    let timer = this.data.countdown;
    const interval = setInterval(() => {
      if (timer <= 0) {
        clearInterval(interval);
        this.setData({
          isSending: false,
          sendBtnText: '重新发送'
        });
        return;
      }
      this.setData({ sendBtnText: `${timer--}s` });
    }, 1000);
  },

  // 重置密码
  async resetPassword() {
    if (!this.validatePasswords()) return;

    this.setData({ isResetting: true });
    try {
      await this.mockApiRequest('resetPassword', {
        newPassword: this.data.newPassword // 明文传输
      });
      this.setData({ currentStep: 3 });
      setTimeout(() => wx.navigateBack(), 3000);
    } catch (error) {
      wx.showToast({ title: error.message, icon: 'none' });
    } finally {
      this.setData({ isResetting: false });
    }
  },

  // 密码验证
  validatePasswords() {
    const valid = this.data.newPassword === this.data.confirmPassword 
                && this.data.newPassword.length >= 6;
    this.setData({
      passwordError: this.data.newPassword.length < 6,
      confirmError: this.data.newPassword !== this.data.confirmPassword
    });
    return valid;
  },

  // 倒计时
  startCountdown() {
    let timer = 60;
    const interval = setInterval(() => {
      if (timer <= 0) {
        clearInterval(interval);
        this.setData({ sendBtnText: '重新发送' });
        return;
      }
      this.setData({ sendBtnText: `${timer--}s` });
    }, 1000);
  },

    // 密码输入处理
  onPasswordChange(e) {
    const password = e.detail;
    this.setData({
      newPassword: password,
      passwordError: password.length > 0 && password.length < 6
    });
  },

  // 确认密码输入处理
  onConfirmPasswordChange(e) {
    const confirmPwd = e.detail;
    this.setData({
      confirmPassword: confirmPwd,
      confirmError: confirmPwd && confirmPwd !== this.data.newPassword
    });
  },

  // 验证密码
  validatePasswords() {
    if (!this.data.newPassword) {
      wx.showToast({
        title: '请输入新密码',
        icon: 'none'
      });
      return false;
    }
    
    if (this.data.newPassword.length < 6) {
      this.setData({ passwordError: true });
      wx.showToast({
        title: '密码不能少于6位',
        icon: 'none'
      });
      return false;
    }

    if (this.data.newPassword !== this.data.confirmPassword) {
      this.setData({ confirmError: true });
      wx.showToast({
        title: '两次输入的密码不一致',
        icon: 'none'
      });
      return false;
    }

    return true;
  },

  // 重置密码
  async resetPassword() {
    if (!this.validatePasswords()) return;

    this.setData({ isResetting: true });
    wx.showLoading({ title: '提交中...' });

    try {
      await new Promise((resolve, reject) => {
        wx.request({
          url: 'https://' + apiDomain + '/api/auth/reset_password',
          method: 'POST',
          data: {
            password: this.data.newPassword
          },
          header: {
            'content-type': 'application/json',
            'Cookie': wx.getStorageSync('sessionid')
          },
          success: (response) => {
            if (response.statusCode === 200) {
              resolve(response);
            } else {
              reject(new Error(response.data.msg || '重置失败'));
            }
          },
          fail: reject
        });
      });

      wx.showToast({
        title: '密码重置成功',
        icon: 'success'
      });

      // 延迟2秒后返回登录页
      setTimeout(() => {
        wx.navigateBack({
          delta: 1
        });
      }, 2000);

    } catch (error) {
      wx.showToast({
        title: error.message || '重置失败',
        icon: 'none'
      });
    } finally {
      this.setData({ isResetting: false });
      wx.hideLoading();
    }
  }

});