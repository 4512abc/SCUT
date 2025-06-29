//由TOTORO编写！！！
package org.example.service;

import com.alibaba.fastjson.JSONObject;
import lombok.extern.slf4j.Slf4j;
import org.bytedeco.javacv.FFmpegFrameGrabber;
import org.bytedeco.javacv.Frame;
import org.bytedeco.javacv.Java2DFrameConverter;
import org.example.common.result.ResultCode;
import org.example.exception.CustomException;
import org.example.mapper.*;
import org.example.model.dto.FileInfoDto.FileInfoDto;
import org.example.model.dto.FileInfoDto.FileUpLoadDto;
import org.example.model.entity.*;
import org.example.model.query.PostQuery.PostCreateQuery;
import org.example.model.query.PostQuery.PostInfoQuery;
import org.example.model.query.PostQuery.PostDeleteQuery;
import org.example.model.utils.Location;
import org.example.model.vo.PostVo.PostCreateVo;
import org.example.model.vo.PostVo.PostInfoVo;
import org.example.model.vo.PostVo.PostDeleteVo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import javax.xml.bind.DatatypeConverter;
import java.util.List;
import java.util.stream.Collectors;

import org.springframework.mock.web.MockMultipartFile;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;
import javax.imageio.ImageIO;
import javax.xml.bind.DatatypeConverter;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import static org.example.common.result.ResultCode.*;
import static org.example.common.result.ResultCode.USER_NOT_EXIST_ERROR;
import static org.example.common.result.ResultCode.POST_NOT_FOUND;
import static org.example.utils.FileUrlUtil.generateFileUrlJson;
import static org.example.utils.FileUrlUtil.getFirstFileFromJsonArray;
@Slf4j
@Service
public class PostService {

    @Autowired
    private PostMapper postMapper;  // 帖子数据访问接口

    @Autowired
    private UserMapper userMapper;  // 用户数据访问接口
    @Autowired
    private LikeMapper likeMapper;  // 点赞数据访问接口
    @Autowired
    private CommentMapper commentMapper;  // 评论数据访问接口

    @Autowired
    private NotificationMapper notificationMapper;  // 通知数据访问接口

    @Autowired
    private FileInfoService fileInfoService;  // 文件信息服务

    /**
     * 获取帖子详情
     * @param query 查询参数对象
     * @return 帖子详情视图对象
     */
    public PostInfoVo getPostDetail(PostInfoQuery query) {
        // 1. 查询帖子基础信息
        PostWithBLOBs post = postMapper.selectPostWithBLOBsById(query.getPostId());
        if (post == null) {
            throw new CustomException(ResultCode.POST_NOT_FOUND);
        }

        // 2. 查询关联用户信息
        User user = userMapper.selectByPrimaryKey(post.getUserId());
        if (user == null) {
            throw new CustomException(ResultCode.USER_NOT_EXIST_ERROR);
        }

        // 3. 构建嵌套VO结构
        PostInfoVo vo = new PostInfoVo();

        // 3.1 构建初始用户信息
        PostInfoVo.InitialInfoVo initialInfo = new PostInfoVo.InitialInfoVo();
        initialInfo.setUserAccount(user.getId());
        initialInfo.setId(user.getAccount()); // 用户昵称使用account字段
        initialInfo.setUserAvatar(user.getAvatar());
        vo.setInitialInfo(initialInfo);

        // 3.2 构建帖子列表信息
        PostInfoVo.PostListVo postList = new PostInfoVo.PostListVo();
        postList.setPostId(post.getId());
        postList.setCover(getFirstFileFromJsonArray(post.getImages()));
        postList.setTitle(post.getTitle());
        postList.setViewCount(post.getViewCount());
        postList.setLikeCount(post.getLikeCount());
        postList.setCommentCount(post.getCommentCount());
        postList.setCreateTime(post.getCreateTime());
        postList.setLocation(Location.fromBytes(post.getLocation()));
        postList.setLandmarkName(post.getLandmarkName());

        vo.setPostList(postList);
        // 3.3 构建帖子详情
        PostInfoVo.PostDetailsVo details = new PostInfoVo.PostDetailsVo();
        details.setContent(post.getContent());
        details.setImages(post.getImages());
        details.setVideos(post.getVideos());
        vo.setDetails(details);

        return vo;
    }

    /**
     * 删除帖子
     * @param query 删除参数对象
     * @param currentUserId 当前用户ID
     * @return 删除结果视图对象
     */
    public PostDeleteVo deletePost(PostDeleteQuery query, Long currentUserId) {
        PostDeleteVo vo = new PostDeleteVo();
        PostWithBLOBs post = postMapper.selectPostWithBLOBsById(query.getPostId());
        if(post == null){
            throw new CustomException(ResultCode.POST_NOT_FOUND);
        }
        User user=userMapper.selectByPrimaryKey(currentUserId);
        // 检查当前用户是否有权限删除该博文
        log.info(" 博文用户ID: {}", user.getAccessLevel());
        if (user.getAccessLevel().equals("user")&&!post.getUserId().equals(currentUserId)) {
            log.info("[调试] 当前用户无权限删除该博文");
            throw new CustomException(ResultCode.PERMISSION_DENIED);
        }

        // 1. 清理点赞相关数据
        processLikeCleanup(post.getId());

        // 2. 清理评论相关数据
        processCommentCleanup(post.getId());

        int result = postMapper.deleteByPrimaryKey(query.getPostId());
        vo.setSuccess(result > 0);
        return vo;
    }

    /**
     * 清理帖子相关的点赞数据
     * @param postId 帖子ID
     */
    private void processLikeCleanup(Long postId) {
        // 查询所有博文相关的点赞记录
        List<Like> likes = likeMapper.selectByTargetIdAndType(postId, "BLOG");

        // 删除相关通知（点赞类型为2）
        likes.forEach(like ->
                notificationMapper.deleteByTypeIdAndType(like.getId(), (byte)2));

        // 删除点赞记录
        if (!likes.isEmpty()) {
            likeMapper.deleteByIds(likes.stream().map(Like::getId).collect(Collectors.toList()));
        }
    }

    /**
     * 清理帖子相关的评论数据
     * @param postId 帖子ID
     */
    private void processCommentCleanup(Long postId) {
        // 查询所有博文相关的评论
        List<Comment> comments = commentMapper.selectByPostId(postId);

        // 删除相关通知（评论类型为1）
        comments.forEach(comment ->
                notificationMapper.deleteByTypeIdAndType(comment.getId(), (byte)1));

        // 删除评论记录
        if (!comments.isEmpty()) {
            commentMapper.deleteByIds(comments.stream().map(Comment::getId).collect(Collectors.toList()));
        }
    }

    /**
     * 创建新帖子
     * @param query 创建参数对象
     * @param currentUserId 当前用户ID
     * @return 创建结果视图对象
     */
    public PostCreateVo createPost(PostCreateQuery query, Long currentUserId) throws Exception {
        PostWithBLOBs post = new PostWithBLOBs();
        post.setUserId(currentUserId);
        post.setTitle(query.getTitle());
        post.setContent(query.getContent());
        post.setImages(query.getImages());
        post.setVideos(query.getVideos());
        post.setIsPublic(query.getIsPublic());
        Location location = Location.fromDoubles(query.getLocation());
        byte[] wkbBytes = location.toBytes();
        // 转换为十六进制字符串
        post.setViewCount(0); // 设置初始浏览数为0
        post.setCommentCount(0);
        post.setStatus((byte) 1);
        post.setLikeCount(0);
        post.setCreateTime(new java.util.Date());
        post.setLocation(wkbBytes); // 需要新增 locationHex 字段
        post.setLandmarkName(query.getLandmarkName());
//        System.out.println("WKB Hex: " + DatatypeConverter.printHexBinary(post.getLocation()));
        if (query.getImages() == "" || query.getImages().isEmpty()) {
            if (query.getVideos() != null && !query.getVideos().isEmpty()) {
                Long id = JSONObject.parseObject(getFirstFileFromJsonArray(query.getVideos())).getLong("id");
                FileInfoDto fileInfoDto =fileInfoService.findById(id);
                MultipartFile file = extractFirstFrameAsMultipartFile(System.getProperty("user.dir")+fileInfoDto.getFilePath() + fileInfoDto.getFileName());
                if(file!=null) {
                    FileUpLoadDto fileUpLoadDto = fileInfoService.add(file);
                    log.info("FileInfoDto: {}", fileInfoDto);
                    post.setImages("["+generateFileUrlJson(fileUpLoadDto.getId())+"]");
                }
            }
        }

        int result = postMapper.insertSelective(post);
        PostCreateVo vo = new PostCreateVo();
        vo.setId(post.getId());
        return vo;
    }

    public static MultipartFile extractFirstFrameAsMultipartFile(String videoUrl) throws Exception {
        // 下载视频到本地临时文件
        File tempVideoFile = new File(videoUrl);
        log.info("tempVideoFile: {}", tempVideoFile);
        // 提取第一帧
        BufferedImage firstFrame = extractFirstFrame(tempVideoFile.getAbsolutePath());
        // 保存为临时图片文件
        if(firstFrame==null)
        {
            log.error("firstFrame is null");
            return null;
        }
        File thumbnailFile = File.createTempFile("thumbnail-", ".jpg");
        if(thumbnailFile==null)
        {
            log.error("thumbnailFile is null");
            return null;
        }
        ImageIO.write(firstFrame, "jpg", thumbnailFile);

        // 转换为 MultipartFile
        return convertToMultipartFile(thumbnailFile);
    }

    private static BufferedImage extractFirstFrame(String videoPath) throws Exception {
        FFmpegFrameGrabber grabber = FFmpegFrameGrabber.createDefault(videoPath);
        Java2DFrameConverter converter = new Java2DFrameConverter();

        try {
            grabber.setOption("skip_frame", "nokey"); // 只抓取关键帧
            grabber.setOption("pix_fmt", "bgr24");    // 提高兼容性
            grabber.start();

            BufferedImage bufferedImage = null;
            int maxAttempts = 61;

            for (int i = 0; i < maxAttempts; i++) {
                Frame frame = grabber.grab();

                if (frame == null || frame.image == null) {
                    log.warn("跳过无效帧: 第 {} 帧", i + 1);
                    continue;
                }

                try {
                    bufferedImage = converter.getBufferedImage(frame);
                    if (bufferedImage != null) {
                        log.info("成功在第 {} 帧提取图像", i + 1);
                        break;
                    }
                } catch (Exception e) {
                    log.warn("第 {} 帧转换异常", i + 1, e);
                }
            }

            grabber.stop();


            return bufferedImage;
        } catch (Exception e) {
            grabber.stop();
            throw e;
        }
    }
    private static MultipartFile convertToMultipartFile(File file) throws IOException {
        try (FileInputStream input = new FileInputStream(file)) {
            ByteArrayOutputStream output = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = input.read(buffer)) != -1) {
                output.write(buffer, 0, bytesRead);
            }

            return new MockMultipartFile(
                    "file",
                    file.getName(),
                    "image/jpeg",
                    output.toByteArray()
            );
        }
    }
}