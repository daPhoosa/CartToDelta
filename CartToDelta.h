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


#ifndef CartToDelta_h
   #define CartToDelta_h

   #include <arduino.h>

   class CartToDelta
   {
      public:
      
      CartToDelta(float armRadius, float armLength);
      
      void input(const float & x, const float & y, const float & z);
      
      float A();
      float B();
      float C();
      
      
      private:
      
      float computeDeltaPos(const float & x1, const float & y1, const float & x2, const float & y2, const float & z);
      float square(float x);
      
      float A_TowerX, A_towerY, B_TowerX, B_towerY, C_TowerX, C_towerY;
      float minArmHeightSq, armLengthSq;
      float A_position, B_position, C_position;
      
   }

   

   
#endif