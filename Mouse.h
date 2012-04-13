//
//  Mouse.h
//  MRMouse
//
//  Created by Mark Rada on 12-03-17.
//  Copyright (c) 2012 Mark Rada. All rights reserved.
//

#import <ApplicationServices/ApplicationServices.h>

CGPoint mouse_current_position();
bool    mouse_move_to(CGPoint);
bool    mouse_move_to(CGPoint,double);
