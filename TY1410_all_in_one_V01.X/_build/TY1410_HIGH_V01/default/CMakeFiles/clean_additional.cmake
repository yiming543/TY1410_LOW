# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "D:\\yiming\\00work\\TY1410_HIGH_V01.X\\out\\TY1410_HIGH_V01\\default.cmf"
  "D:\\yiming\\00work\\TY1410_HIGH_V01.X\\out\\TY1410_HIGH_V01\\default.hex"
  "D:\\yiming\\00work\\TY1410_HIGH_V01.X\\out\\TY1410_HIGH_V01\\default.hxl"
  "D:\\yiming\\00work\\TY1410_HIGH_V01.X\\out\\TY1410_HIGH_V01\\default.mum"
  "D:\\yiming\\00work\\TY1410_HIGH_V01.X\\out\\TY1410_HIGH_V01\\default.o"
  "D:\\yiming\\00work\\TY1410_HIGH_V01.X\\out\\TY1410_HIGH_V01\\default.sdb"
  "D:\\yiming\\00work\\TY1410_HIGH_V01.X\\out\\TY1410_HIGH_V01\\default.sym"
  )
endif()
