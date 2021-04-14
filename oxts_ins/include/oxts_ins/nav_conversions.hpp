/**
 * @file convert.hpp
 * @brief General purpose conversion functions between coordinate frames.
 */

#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <vector>
#include <math.h>

#include "oxts_ins/nav_const.hpp"


namespace Point
{

class Point
{
private:
  double x_0 = 0;
  double x_1 = 0;
  double x_2 = 0;
public:
  double x0(){ return x_0; };
  double x1(){ return x_1; };
  double x2(){ return x_2; };
  void   x0(double x_0){this->x_0 = x_0;}
  void   x1(double x_1){this->x_1 = x_1;}
  void   x2(double x_2){this->x_2 = x_2;}
};

class Cart : protected Point
{
public:
  double x(){ return x0(); }
  double y(){ return x1(); }
  double z(){ return x2(); }
  void   x(double x){ x0(x); }
  void   y(double y){ x1(y); }
  void   z(double z){ x2(z); }
};

class LLA : protected Point
{
public:
  double lat(){ return x0(); }
  double lon(){ return x1(); }
  double alt(){ return x2(); }
  void   lat(double x){ x0(x); }
  void   lon(double y){ x1(y); }
  void   alt(double z){ x2(z); }
};

}



/**
 * @namespace NavConversions
 * @brief Functions to convert measurements between frames etc.
 */
namespace NavConversions
{
  /**
   * @fn hpr_to_quaternion
   * @brief Convert Euler angles (Heading, Pitch, Roll) to Quaternions. 
   * 
   * @param  h Heading (deg)
   * @param  p Pitch   (deg)
   * @param  r Roll    (deg)
   * @return Quaternion (x, y, z, w)
   */
  std::vector<double> hpr_to_quaternion(double h, double p, double r);
  /**
   * @fn lla_to_ecef
   * @brief Convert Lat, Long, Alt to ECEF x,y,z 
   * 
   * @param  lat Latitude in WGS84
   * @param  lon Longitude in WGS84
   * @param  alt Altitude in WGS84
   * @return ECEF (x, y, z)
   */
  std::vector<double> lla_to_ecef(double lat, double lon, double alt);
  /** Converts WGS-84 Geodetic point (lat, lon, alt) to the 
   * Earth-Centered Earth-Fixed (ECEF) coordinates (x, y, z)
   */
  Point::Cart GeodeticToEcef(double lat, double lon, double alt);
  /** Converts the Earth-Centered Earth-Fixed (ECEF) coordinates (x, y, z) to 
   * (WGS-84) Geodetic point (lat, lon, h).
   */
  Point::LLA EcefToGeodetic(double x, double y, double z);
  /** Converts the Earth-Centered Earth-Fixed (ECEF) coordinates (x, y, z) to 
   * East-North-Up coordinates in a Local Tangent Plane that is centered at the 
   * (WGS-84) Geodetic point (lat0, lon0, alt).
   */
  Point::Cart EcefToEnu(double x, double y, double z,
                        double lat0, double lon0, double alt
                        );
  /** Inverse of EcefToEnu. Converts East-North-Up coordinates 
   * (xEast, yNorth, zUp) in a Local Tangent Plane that is centered at the 
   * (WGS-84) Geodetic point (lat0, lon0, alt0) to the 
   * Earth-Centered Earth-Fixed (ECEF) coordinates (x, y, z).
   */
  Point::Cart EnuToEcef(double xEast, double yNorth, double zUp,
                        double lat0, double lon0, double alt0
                        );
  /** Converts the East-North-Up coordinates into a local coordinate frame 
   *  defined at the same origin, but rotated around the negative z-axis by 
   *  ref_heading degrees. Designed for use with the LRF from NCom.
   */
  Point::Cart EnuToLrf(double xEast, double yNorth, double zUp, double ref_heading);


  /** Converts the geodetic WGS-84 coordinated (lat, lon, h) to 
   * East-North-Up coordinates in a Local Tangent Plane that is centered at the 
   * (WGS-84) Geodetic point (lat0, lon0, alt0).
   */
  Point::Cart GeodeticToEnu(double lat, double lon, double h,
                            double lat0, double lon0, double alt0
                            );
}

#endif // CONVERSIONS_HPP