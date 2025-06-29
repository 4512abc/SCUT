package org.example.utils;

import lombok.extern.slf4j.Slf4j;
import org.example.model.utils.Location;

@Slf4j
public class LocationDistance {
    private static final double EARTH_RADIUS_KM = 6371.0;
    public static double calculateDistance(Location location1, Location location2) {
        double lat1 = location1.getLat();
        log.info("lat1:"+lat1);
        double lon1 = location1.getLng();
        log.info("lon1:"+lon1);
        double lat2 = location2.getLat();
        log.info("lat2:"+lat2);
        double lon2 = location2.getLng();
        log.info("lon2:"+lon2);
        double dLat = Math.toRadians(lat2 - lat1);
        double dLon = Math.toRadians(lon2 - lon1);

        lat1 = Math.toRadians(lat1);
        lat2 = Math.toRadians(lat2);

        double a = Math.sin(dLat / 2) * Math.sin(dLat / 2) +
                Math.cos(lat1) * Math.cos(lat2) *
                        Math.sin(dLon / 2) * Math.sin(dLon / 2);
        double c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));

        return EARTH_RADIUS_KM * c;
    }

    /**
     * 判断一个经纬度点是否在以另一个经纬度点为圆心、半径为 r 的范围内
     * @param r 半径（单位：公里）
     * @return 如果在范围内则返回 true，否则返回 false
     */
    public static boolean isWithinRadius(Location location1, Location location2,double r) {
        double distance = calculateDistance(location1,location2)*1000;
        log.info("distance:"+distance+"m");
        return distance <= r;
    }
}
