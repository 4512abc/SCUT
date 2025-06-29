//package org.example;
//
//import cn.hutool.crypto.SecureUtil;
//import org.example.entity.userDto;
//import org.example.entity.userTest;
//import org.example.entity.userVo;
//import org.example.utils.EmailUtil;
//import org.junit.jupiter.api.Test;
//import org.mybatis.generator.api.MyBatisGenerator;
//import org.mybatis.generator.config.Configuration;
//import org.mybatis.generator.config.xml.ConfigurationParser;
//import org.mybatis.generator.internal.DefaultShellCallback;
//import org.springframework.beans.BeanUtils;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.boot.test.context.SpringBootTest;
//import org.springframework.mail.SimpleMailMessage;
//import org.springframework.mail.javamail.JavaMailSender;
//
//import java.io.File;
//import java.util.ArrayList;
//import java.util.List;
//
//@SpringBootTest
//class GenerateApplicationTests {
//
//    @Autowired
//    private JavaMailSender mailSender;
//
//    @Test
//    void contextLoads() throws Exception {
//        List<String> warnings = new ArrayList<String>();
//        boolean overwrite = true;
//        // 下一行中的是存放generator配置的路径，切记不要写错
//        File configFile = new File("src/main/resources/generatorConfig.xml");
//        ConfigurationParser cp = new ConfigurationParser(warnings);
//        Configuration config = cp.parseConfiguration(configFile);
//        DefaultShellCallback callback = new DefaultShellCallback(overwrite);
//        MyBatisGenerator myBatisGenerator = new MyBatisGenerator(config, callback, warnings);
//        myBatisGenerator.generate(null);
//    }
//
//    @Test
//    void testMd5() {
//        String password = SecureUtil.md5("123456");
//        System.out.println(password);
//    }
//
//    @Test
//    void testBean() throws Exception {
//        userVo userVo=new userVo();
//        userDto userDto=new userDto();
//        userTest userTest=new userTest();
//        BeanUtils.copyProperties(userTest,userDto);
//
//    }
//}
