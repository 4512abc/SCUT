const { apiDomain } = require("../../../config");

// register.js
Page({
  data: {
    email: '',
    captcha: '',
    password: '',
    isLoading: false,
    isCaptchaSending: false,
    captchaText: '获取验证码',
    captchaTimer: 60,
    emailError: false,
    passwordError: false
  },

  // 输入处理
  onEmailChange(e) {
    const value = e.detail;
    const emailRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;
    this.setData({
      email: value,
      emailError: !emailRegex.test(value)
    });
  },

  onCaptchaChange(e) {
    this.setData({ captcha: e.detail.substring(0, 6) });
  },

  onPasswordChange(e) {
    const value = e.detail;
    const isValid = value.length >= 6;
    this.setData({
      password: value,
      passwordError: !isValid
    });
  },

  // 发送验证码
  async sendCaptcha() {
    // 如果正在倒计时中，直接返回
    if (this.data.isCaptchaSending || this.data.captchaText !== '获取验证码' && this.data.captchaText !== '重新获取') {
      console.log('[调试] 倒计时中，禁止重复发送');
      return;
    }
  
    console.log('[调试] 开始发送验证码流程');
    console.log('[调试] 当前邮箱:', this.data.email);
  
    if (!this.validateEmail()) {
      console.log('[调试] 邮箱验证失败');
      return;
    }
  
    this.setData({ isCaptchaSending: true });
    wx.showLoading({ title: '发送中...' });
  
    const requestData = {
      email: this.data.email
    };
    console.log('[调试] 发送验证码请求数据:', requestData);
  
    try {
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: 'https://' + apiDomain + '/api/auth/email_code',
          method: 'POST',
          data: requestData,
          header: {
            'content-type': 'application/json'
          },
          success: (response) => {
            console.log('[调试] 验证码请求完整响应:', response);
            if (response.statusCode === 200) {
              resolve(response);
            } else {
              reject(new Error(response.data.msg || '请求失败'));
            }
          },
          fail: (error) => {
            console.error('[调试] 请求失败:', error);
            reject(error);
          }
        });
      });
  
      // 保存sessionid
      if (res.header['set-cookie']) {
        wx.setStorageSync('sessionid', res.header['set-cookie']);
      } else if (res.header['Set-Cookie']) {
        wx.setStorageSync('sessionid', res.header['Set-Cookie']);
      }
  
      console.log('[调试] 验证码请求成功');
      this.startCountdown();
      wx.showToast({
        title: res.data.msg || '验证码已发送',
        icon: 'success'
      });
  
    } catch (error) {
      console.error('[调试] 验证码发送异常:', error);
      wx.showToast({
        title: error.message || '发送失败',
        icon: 'none'
      });
      // 发送失败时重置状态
      this.setData({
        isCaptchaSending: false,
        captchaText: '重新获取'
      });
    } finally {
      wx.hideLoading();
    }
  },

  // 注册提交
  async handleRegister() {
    console.log('[调试] 开始注册流程');
    
    const requestData = {
      email: this.data.email,
      code: this.data.captcha,
      password: this.data.password
    };
    console.log('[调试] 注册请求数据:', requestData);
    
    if (!this.validateAll()) {
      console.log('[调试] 表单验证失败');
      return;
    }
    
    this.setData({ isLoading: true });
    wx.showLoading({ title: '注册中...' });
    
    try {
      const res = await new Promise((resolve, reject) => {
        wx.request({
          url: 'https://' + apiDomain + '/api/auth/register',  // 修正URL
          method: 'POST',
          data: requestData,
          header: {
            'content-type': 'application/json',
            'Cookie': wx.getStorageSync('sessionid')
          },
          success: (response) => {
            console.log('[调试] 完整注册响应:', response);
            console.log('[调试] 响应状态码:', response.statusCode);
            console.log('[调试] 响应数据:', response.data);
            
            // 只要服务器正常响应就resolve
            if (response.statusCode === 200) {
              resolve(response);
            } else {
              reject(new Error(response.data.msg || '注册失败'));
            }
          },
          fail: (error) => {
            console.error('[调试] 请求失败:', error);
            reject(error);
          }
        });
      });
  
      console.log('[调试] 解析响应数据:', res.data);
      
      // 修改判断逻辑
      if (res.data && (res.data.code === 200 || res.data.msg === '成功')) {
        console.log('[调试] 注册成功，准备跳转');
        wx.showToast({ 
          title: '注册成功', 
          icon: 'success',
          duration: 1500,
          complete: () => {  // 改用complete回调
            setTimeout(() => {
              console.log('[调试] 开始跳转到登录页');
              wx.navigateBack({
                delta: 1,
                success: () => console.log('[调试] 返回成功'),
                fail: (error) => console.error('[调试] 返回失败:', error)
              });
            }, 1500);
          }
        });
      } else {
        throw new Error(res.data.msg || '注册失败');
      }
  
    } catch (error) {
      console.error('[调试] 注册异常:', error);
      wx.showToast({ 
        title: error.message || '注册失败', 
        icon: 'none' 
      });
    } finally {
      this.setData({ isLoading: false });
      wx.hideLoading();
    }
  },

  // 验证逻辑
  validateEmail() {
    const emailRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;
    const isValid = emailRegex.test(this.data.email);
    this.setData({ emailError: !isValid });
    return isValid;
  },

  validateAll() {
    return [
      this.validateEmail(),
      this.data.password.length >= 6,
      this.data.captcha.length === 6
    ].every(Boolean);
  },

  // 倒计时逻辑
  startCountdown() {
    let timer = 60;
    const interval = setInterval(() => {
      if (timer <= 0) {
        clearInterval(interval);
        this.setData({ 
          isCaptchaSending: false,
          captchaText: '重新获取'
        });
        return;
      }
      this.setData({ captchaText: `${timer--}s` });
    }, 1000);
  }
});