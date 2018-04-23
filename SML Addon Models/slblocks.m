function blkStruct = slblocks

blkStruct.OpenFcn = {'NLGCToolbox','NLGCTestSuite'}; 

Browser(1).Library = 'NLGCToolbox'; 

Browser(1).Name    = 'Thinh - NLGC for Quadrotor'; 

Browser(1).IsFlat  = 1;

Browser(2).Library = 'NLGCTestSuite'; 

Browser(2).Name    = 'Thinh - NLGC Test Suite'; 

Browser(2).IsFlat  = 1;% Is this library "flat" (i.e. no subsystems)?

blkStruct.Browser = Browser; 