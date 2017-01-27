/*
   Cartesian to Delta Converter
   Phillip Schmidt
   v0.1

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.
      
      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.
      
      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

/*
   Tower A is front left
   Tower B is front right
   Tower C is rear center
   
   armRadius = horizontal component of arm length (in Marlin this is DELTA_RADIUS )
   armLength = length of arm measured center-to-center of pivot points
   
   Kossel v2.2 numbers
      armRadius = 109 = 155 - 24 - 22 // mm
      armLength = 217.3 // mm
   
*/


#include "CartToDelta.h"


   CartToDelta::CartToDelta(float armRadius, float armLength)
   {

      const float sin60 = 0.86602540378f
      const float cos60 = 0.5f
      
      A_TowerX = -sin60 * armRadius;
      A_towerY = -cos60 * armRadius;
      B_TowerX =  sin60 * armRadius;
      B_towerY = -cos60 * armRadius;
      C_TowerX =  0.0f;
      C_towerY =  armRadius;
      
      armLengthSq = armLength * armLength;
      
      minArmHeightSq = square( 0.258819f * armLength );  // sin(15deg) * armLength
   }
   
   
   void CartToDelta::input( const float & x, const float & y, const float & z )
   {
      // an axis that is asked to go to an unreachable location will fail silently and remain at its old location

      float temp;
      
      temp = computeDeltaPos( A_TowerX, A_TowerY, x, y, z );
      if( temp > 0.0f )
      {
         A_position = temp;
      }

      temp = computeDeltaPos( B_TowerX, B_TowerY, x, y, z );
      if( temp > 0.0f )
      {
         B_position = temp;
      }

      temp = computeDeltaPos( C_TowerX, C_TowerY, x, y, z );
      if( temp > 0.0f )
      {
         C_position = temp;
      }

   }

   
   float CartToDelta::computeDeltaPos( const float & x1, const float & y1, const float & x2, const float & y2, const float & z )
   {
      static float dx_Sq, dy_Sq, dz_Sq;
      
      dx_Sq = square( x1 - x2 );
      
      dy_Sq = square( y1 - y2 );
      
      dz_Sq = armLengthSq - (dx_Sq + dy_Sq);
      
      if( dz_Sq > minArmHeightSq )
      {
         return sqrt(dz_Sq) + z;
      }
      else
      {
         return -1.0f;  // failure
      }
   }

   
   float CartToDelta::square( float x )
   {
      return x * x;
   }
   
   
   float CartToDelta::A()
   {
      return A_position;
   }
   
   
   float CartToDelta::B()
   {
      return B_position;
   }
   
   
   float CartToDelta::C()
   {
      return C_position;
   }   
