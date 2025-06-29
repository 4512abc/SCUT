const { apiDomain } = require('../../../config.js');
const config = require('../../../config.js')

Page({
  data: {
    isEmailLogin: true,  // 默认使用邮箱登录
    account: '',         // 统一使用 account 存储邮箱或用户名
    password: '',
  },

  // 切换登录方式
  switchLoginType() {
    this.setData({
      isEmailLogin: !this.data.isEmailLogin,
      account: ''  // 切换时清空输入框
    });
  },

 // 输入框事件处理
  onAccountChange(e) {
    this.setData({
      account: e.detail
    });
  },

  onPasswordChange(e) {
    this.setData({
      password: e.detail
    });
  },

  // 登录处理
  handleLogin() {
    const { account, password, isEmailLogin } = this.data;
    // 表单验证
    if (!account || !account.trim()) {
      wx.showToast({
        title: isEmailLogin ? '请输入邮箱' : '请输入用户名',
        icon: 'none'
      });
      return;
    }
    // 邮箱格式验证
    if (isEmailLogin) {
      const emailRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;
      if (!emailRegex.test(account)) {
        wx.showToast({
          title: '邮箱格式不正确',
          icon: 'none'
        });
        return;
      }
    }

    if (!password || password.length < 6) {
      wx.showToast({
        title: '密码至少6位',
        icon: 'none'
      });
      return;
    }

    // 发起登录请求
    console.log('[调试] 开始登录请求');
    wx.showLoading({ title: '登录中...' });
    wx.request({
        url: 'https://' + apiDomain + '/api/auth/login',
        method: 'POST',
        data: {
            loginType: isEmailLogin ? 'email' : 'username',
            account: account.trim(),
            password: password
        },
        success: (res) => {
            console.log('[调试] 登录响应:', res.data);
            if (res.data.code === "0") {
                const { token, userInfo } = res.data.data;
                console.log('[调试] 获取到的token:', token);
                console.log('[调试] 获取到的用户信息:', userInfo);

                try {
                    // 存储用户信息和token
                    wx.setStorageSync('token', token);
                    wx.setStorageSync('userInfo', userInfo);
                    console.log('[调试] 数据存储成功');

                    // 直接使用reLaunch跳转
                    wx.reLaunch({
                        url: '/pages/index/index',
                        success: () => {
                            console.log('[调试] 跳转成功');
                        },
                        fail: (error) => {
                            console.error('[调试] 跳转失败:', error);
                            wx.showToast({
                                title: '跳转失败',
                                icon: 'none'
                            });
                        }
                    });
                } catch (error) {
                    console.error('[调试] 处理过程出错:', error);
                    wx.showToast({
                        title: '登录异常，请重试',
                        icon: 'none'
                    });
                }
            } else {
                console.error('[调试] 登录失败:', res.data.msg);
                wx.showToast({
                    title: res.data.msg || '登录失败',
                    icon: 'none'
                });
            }
        },
        fail: (err) => {
            console.error('[调试] 网络请求失败:', err);
            wx.showToast({
                title: '网络错误，请稍后重试',
                icon: 'none'
            });
        },
        complete: () => {
            wx.hideLoading();
            console.log('[调试] 登录请求完成');
        }
    });
  },

  // 导航事件
  navigateToForgotPwd() {
    wx.navigateTo({ url: '/pages/login_related/forget_password/forget_password' });
  },
  navigateToRegister() {
    wx.navigateTo({ url: '/pages/login_related/register/register' });
  },
  navigateToAgreement() {
    wx.navigateTo({ url: '/pages/agreement/agreement' });
  },
 
  // 密码可见切换
  togglePassword() {
    this.setData({ showPassword: !this.data.showPassword });
  },

  async handleWechatLogin() {
    try {
        wx.showLoading({
            title: '登录中...',
            mask: true
        });
        console.log('[调试] 开始微信登录流程');
        
        // 获取用户信息
        const userProfile = await this.getWechatUserProfile();
        console.log('[调试] 用户信息:', userProfile);
        
        // 获取登录凭证
        const loginRes = await this.wxLogin();
        console.log('[调试] 登录凭证:', loginRes);
        
        // 调用后端接口
        const apiRes = await this.callLoginAPI({
            code: loginRes.code,
            encryptedData: userProfile.encryptedData,
            iv: userProfile.iv
        });
        
        // 处理登录成功
        await this.handleLoginSuccess(apiRes.data);
        
    } catch (error) {
        console.error('[调试] 登录失败:', error);
        wx.showToast({
            title: error.message || '登录失败',
            icon: 'none'
        });
    } finally {
        wx.hideLoading();
    }
  },

  // 获取微信用户信息
  getWechatUserProfile() {
    return new Promise((resolve, reject) => {
      wx.getUserProfile({
        desc: '用于登录获取用户信息',
        success: res => resolve(res),
        fail: err => reject(new Error('用户拒绝授权'))
      })
    })
  },

  // 微信登录获取code
  wxLogin() {
    return new Promise((resolve, reject) => {
      wx.login({
        success: res => {
          console.log('[调试] wx.login响应:', res)
          if (res.code) {
            console.log('[调试] 成功获取code:', res.code)
            resolve(res)
          } else {
            console.error('[调试] code获取失败:', res)
            reject(new Error('登录失败[code获取失败]'))
          }
        },
        fail: (err) => {
          console.error('[调试] wx.login失败:', err)
          reject(new Error('微信登录失败'))
        }
      })
    })
  },

  // 调用服务端接口
  async callLoginAPI(params) {
    try {
        console.log('[调试] 开始调用登录接口, 参数:', params);

        const res = await new Promise((resolve, reject) => {
            wx.request({
                url: 'https://' + apiDomain + '/api/auth/wechat_login',
                method: 'POST',
                data: {
                    code: params.code,
                    encryptedData: params.encryptedData,
                    iv: params.iv
                },
                header: { 'Content-Type': 'application/json' },
                success: (response) => {
                    console.log('[调试] 登录接口响应:', response);
                    // 从header中获取token
                    const token = response.header['Authorization'] || response.header['authorization'];
                    console.log('[调试] 从header获取的token:', token);
                    
                    // 存储token
                    if (token) {
                        wx.setStorageSync('token', token);
                        console.log('[调试] token存储成功:', wx.getStorageSync('token'));
                    }
                    resolve(response);
                },
                fail: reject
            });
        });

        return res;
    } catch (error) {
        console.error('[调试] 登录请求失败:', error);
        throw error;
    }
  },

  // 处理登录成功的方法
  handleLoginSuccess(data) {
    try {
        console.log('[调试] 开始处理登录成功');
        // 只存储用户信息，token已在callLoginAPI中处理
        wx.setStorageSync('userInfo', data);
        console.log('[调试] 用户信息存储成功');
        
        wx.showToast({
            title: '登录成功',
            icon: 'success',
            duration: 1500,
            success: () => {
                setTimeout(() => {
                    wx.reLaunch({
                        url: '/pages/index/index',
                        success: () => {
                            console.log('[调试] 跳转首页成功');
                        },
                        fail: (error) => {
                            console.error('[调试] 跳转失败:', error);
                        }
                    });
                }, 1500);
            }
        });
    } catch (error) {
        console.error('[调试] 处理登录成功时发生错误:', error);
        throw error;
    }
  },

  // 错误处理
  handleLoginError(error) {
    console.error('登录失败:', error);
    wx.showToast({
      title: error.message || '登录失败',
      icon: 'none',
      duration: 2000
    });
  }

  
});