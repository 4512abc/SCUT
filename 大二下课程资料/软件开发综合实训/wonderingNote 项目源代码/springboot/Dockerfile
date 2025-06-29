# 使用Maven构建
FROM maven:3.8.4-openjdk-11 AS build
WORKDIR /wonderingNote  
COPY pom.xml .
COPY src ./src
RUN mvn clean package -DskipTests

# 使用JRE运行
FROM openjdk:11-jre-slim
WORKDIR /app
COPY --from=build /app/target/*.jar app.jar
EXPOSE 8080
ENTRYPOINT ["java", "-jar", "app.jar"]