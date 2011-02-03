#define BOOST_TEST_MODULE BaseTypes
#include <boost/test/included/unit_test.hpp>

#include "base/angle.h"
#include "base/time.h"
#include "base/timemark.h"
#include "base/pose.h"
#include "base/samples/imu.h"
#include "base/samples/laser_scan.h"
#include "base/samples/sonar_scan.h"
#include "base/samples/rigid_body_state.h"

#include <Eigen/SVD>
#include <Eigen/LU>

using namespace std;

BOOST_AUTO_TEST_CASE( pose_test )
{
    Eigen::Vector3d pos( 10, -1, 20.5 );
    Eigen::Quaterniond orientation( Eigen::AngleAxisd( 0.2, Eigen::Vector3d(0.5, 1.4, 0.1) ) );

    base::Pose p( pos, orientation ); 
    Eigen::Transform3d t( p.toTransform() );

    BOOST_CHECK( pos.isApprox( t.translation() ) );
    BOOST_CHECK( orientation.isApprox( Eigen::Quaterniond(t.rotation()), 0.01 ) );

    cout << Eigen::Quaterniond(t.rotation()).coeffs().transpose() << endl;
    cout << orientation.coeffs().transpose() << endl;
}

BOOST_AUTO_TEST_CASE( angle_test )
{
    using namespace base;

    Angle a = Angle::fromDeg( 90 );
    BOOST_CHECK( a.isApprox( Angle::fromRad( M_PI/2.0 )) );
    BOOST_CHECK( a.isApprox( Angle::fromDeg( 90 + 720 )) );
    BOOST_CHECK( a.isApprox( Angle::fromDeg( 90 ) + Angle::fromDeg( 720 )) );
    BOOST_CHECK( a.isApprox( Angle::fromDeg( 90 - 720 )) );
    BOOST_CHECK( a.isApprox( Angle::fromDeg( 90 ) - Angle::fromDeg( 720 )) );
    BOOST_CHECK( (2*a).isApprox( Angle::fromDeg( 180 )) );
    BOOST_CHECK_CLOSE( (Angle::fromDeg(45)+Angle::fromDeg(-45)).getRad(), Angle::fromRad(0).getRad(), 1e-3 );
    std::cout << a << std::endl;
}
