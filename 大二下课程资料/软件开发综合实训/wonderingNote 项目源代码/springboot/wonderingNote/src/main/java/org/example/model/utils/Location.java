package org.example.model.utils;
import org.locationtech.jts.geom.GeometryFactory;
import org.locationtech.jts.geom.Point;
import org.locationtech.jts.io.ByteOrderValues;
import org.locationtech.jts.io.WKBReader;
import lombok.Data;
import org.locationtech.jts.io.WKBWriter;
import org.locationtech.jts.geom.GeometryFactory;
import org.locationtech.jts.geom.Coordinate;
import lombok.Data;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import lombok.extern.slf4j.Slf4j;
import org.springframework.context.annotation.ComponentScan;

import javax.xml.bind.DatatypeConverter;

//统一在数据库中使用Byte[]进行存储，在前端使用Double进行存储！
@Data
@Slf4j
public class Location {
    private static final int DOUBLE_BYTE_SIZE = 8; // 每个double占8字节

    private Double lng;
    private Double lat;

    /**
     * 从byte数组构造Location对象
     * @param wkbBytes 数据库存储的byte数组(16字节)
     * @throws IllegalArgumentException 如果输入byte数组长度不正确
     */
    public Location(byte[] wkbBytes) throws Exception {
        WKBReader reader = new WKBReader();
        Point point = (Point) reader.read(wkbBytes);
        this.lng = point.getX();
        this.lat = point.getY();
    }
    /**
     * 通过经纬度构造Location对象
     * @param lng 经度
     * @param latitude 纬度
     */
    public Location(Double lng, Double latitude) {
        this.lng = lng;
        this.lat = latitude;
    }

    /**
     * 转换为数据库存储的byte数组
     * @return 16字节的byte数组
     */
    // 修改后的 toBytes() 方法

    public byte[] toBytes() {
        if (lng == null || lat == null) return null;

        ByteBuffer buffer = ByteBuffer.allocate(21) // 1+4+8+8=21字节
                .order(ByteOrder.BIG_ENDIAN)
                .put((byte) 0x00)     // 1字节：大端序标记
                .putInt(1)            // 4字节：几何类型（Point=1）
                .putDouble(lat)       // 8字节：经度
                .putDouble(lng);      // 8字节：纬度

        byte[] wkb = buffer.array();
        System.out.println(javax.xml.bind.DatatypeConverter.printHexBinary(wkb).toUpperCase());
        return wkb;
    }

    /**
     * 转换为前端使用的double数组
     * @return [经度, 纬度]
     */
    public double[] toDoubleArray() {
        return new double[]{
                lng != null ? lng : 0.0,
                lat != null ? lat : 0.0
        };
    }

    /**
     * 验证byte数组是否有效
     * @param bytes 待验证的byte数组
     * @return 是否有效
     */
    public static boolean isValidBytes(byte[] bytes) {
        return bytes != null && bytes.length == 21;  // WKB Point的标准长度
    }
    /**
     * 静态方法：从byte数组创建Location对象
     */
    public static Location fromBytes(byte[] locationBytes) {
        if (locationBytes == null) {
            return null;
        }
        try {
            String wktString = new String(locationBytes);
            // 去除 "POINT(" 前缀和 ")" 后缀
            String coordsStr = wktString.substring(6, wktString.length() - 1);
            String[] coords = coordsStr.split(" ");

            if (coords.length == 2) {
                double latitude = Double.parseDouble(coords[0]);
                double longitude = Double.parseDouble(coords[1]);
                return new Location(longitude, latitude);
            }
        } catch (Exception e) {

        }
        return null;



    }
    /**
     * 静态方法：从double数组创建Location对象
     */
    public static Location fromDoubles(Double[] coordinates) {
        log.info("coordinates:{}",coordinates);
        if (coordinates == null || coordinates.length != 2) {
            throw new IllegalArgumentException("Invalid coordinates array");
        }
        return new Location(coordinates[0], coordinates[1]);
    }
}