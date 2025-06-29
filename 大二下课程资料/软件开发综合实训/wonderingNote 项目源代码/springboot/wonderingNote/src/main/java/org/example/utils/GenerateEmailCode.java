package org.example.utils;

import java.util.Random;

public class GenerateEmailCode {
    public String generateVerificationCode() {
        Random random = new Random();
        int code = 100000 + random.nextInt(900000); // 生成6位数验证码
        return String.valueOf(code);
    }
}
