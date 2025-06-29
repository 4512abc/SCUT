package org.example;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import tk.mybatis.spring.annotation.MapperScan;

@MapperScan("org.example.mapper")
@SpringBootApplication
public class wonderingNoteApplication
{
    public static void main(String[] args) {

        SpringApplication.run(wonderingNoteApplication.class, args);
    }
}
