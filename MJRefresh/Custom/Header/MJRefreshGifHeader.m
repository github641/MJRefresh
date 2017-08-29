//
//  MJRefreshGifHeader.m
//  MJRefreshExample
//
//  Created by MJ Lee on 15/4/24.
//  Copyright (c) 2015年 小码哥. All rights reserved.
//
/* lzy170828注:
 视图层级：
 MJRefreshNormalHeaderView，
 子视图有：
 上半部分的操作提示文字，
 下半部分更新的时间，
 centerY在这两个label连接点的UIActivityIndicatorView或者arrowImageView
 
 */

#import "MJRefreshGifHeader.h"

@interface MJRefreshGifHeader()
{
    __unsafe_unretained UIImageView *_gifView;
}
/** 所有状态对应的动画图片 */
@property (strong, nonatomic) NSMutableDictionary *stateImages;
/** 所有状态对应的动画时间 */
@property (strong, nonatomic) NSMutableDictionary *stateDurations;
@end

@implementation MJRefreshGifHeader
#pragma mark - 懒加载
- (UIImageView *)gifView
{
    if (!_gifView) { 
        UIImageView *gifView = [[UIImageView alloc] init]; 
        [self addSubview:_gifView = gifView]; 
    } 
    return _gifView; 
}

- (NSMutableDictionary *)stateImages 
{ 
    if (!_stateImages) { 
        self.stateImages = [NSMutableDictionary dictionary]; 
    } 
    return _stateImages; 
}

- (NSMutableDictionary *)stateDurations 
{ 
    if (!_stateDurations) { 
        self.stateDurations = [NSMutableDictionary dictionary]; 
    } 
    return _stateDurations; 
}

#pragma mark - 公共方法
- (void)setImages:(NSArray *)images duration:(NSTimeInterval)duration forState:(MJRefreshState)state 
{ 
    if (images == nil) return; 
    
    self.stateImages[@(state)] = images; 
    self.stateDurations[@(state)] = @(duration); 
    
    /* 根据图片设置控件的高度 */ 
    UIImage *image = [images firstObject]; 
    if (image.size.height > self.mj_h) { 
        self.mj_h = image.size.height; 
    } 
}

- (void)setImages:(NSArray *)images forState:(MJRefreshState)state 
{ 
    [self setImages:images duration:images.count * 0.1 forState:state]; 
}

#pragma mark - 实现父类的方法
// lzy170828注：部分重写
- (void)prepare
{
    [super prepare];
    
    // 初始化间距
    self.labelLeftInset = 20;
}
// lzy170828注：部分重写。父类中是，根据拖拽进度设置透明度
- (void)setPullingPercent:(CGFloat)pullingPercent
{
    [super setPullingPercent:pullingPercent];
    NSArray *images = self.stateImages[@(MJRefreshStateIdle)];
    if (self.state != MJRefreshStateIdle || images.count == 0) return;
    // 停止动画
    [self.gifView stopAnimating];
    // 设置当前需要显示的图片
    NSUInteger index =  images.count * pullingPercent;
    if (index >= images.count) index = images.count - 1;
    self.gifView.image = images[index];
}
// lzy170828注：部分重写
- (void)placeSubviews
{
    [super placeSubviews];
    
    if (self.gifView.constraints.count) return;
    
    self.gifView.frame = self.bounds;
    if (self.stateLabel.hidden && self.lastUpdatedTimeLabel.hidden) {
        // lzy170828注：没有操作提示label和时间label，那么把gifView放置到中间
        self.gifView.contentMode = UIViewContentModeCenter;
    } else {
        self.gifView.contentMode = UIViewContentModeRight;
        
        CGFloat stateWidth = self.stateLabel.mj_textWith;
        CGFloat timeWidth = 0.0;
        if (!self.lastUpdatedTimeLabel.hidden) {
            timeWidth = self.lastUpdatedTimeLabel.mj_textWith;
        }
        CGFloat textWidth = MAX(stateWidth, timeWidth);
        /* lzy170828注:
         1、类比(self.mj_w - textWidth) * 0.5，就是根据stateLabel和timeLabel中宽度更大的那个，把它摆到self的中间，此时算出来的x坐标
         2、self.labelLeftInset，是label和gifView的间距
         3、由于gifView的X坐标是0，所以算出来的就是gifView的宽度
         */
        self.gifView.mj_w = self.mj_w * 0.5 - textWidth * 0.5 - self.labelLeftInset;
    }
}
// lzy170828注：完全重写
/* lzy170829注:
 不是完全重写，都是部分重写，先或者后调用父类的方法。
 这个方法的父类方法的调用在宏里面：
 // 状态检查
 #define MJRefreshCheckState \
 MJRefreshState oldState = self.state; \
 if (state == oldState) return; \
 [super setState:state];
 */

- (void)setState:(MJRefreshState)state
{
    MJRefreshCheckState
    
    // 根据状态做事情
    if (state == MJRefreshStatePulling || state == MJRefreshStateRefreshing) {
        
        // lzy170828注：把存在字典中的，对应状态的图片数组取出来，处理图片个数为0，为1，多张图片的情况
        NSArray *images = self.stateImages[@(state)];
        if (images.count == 0) return;
        
        [self.gifView stopAnimating];
        if (images.count == 1) { // 单张图片
            self.gifView.image = [images lastObject];
        } else { // 多张图片
            self.gifView.animationImages = images;
            self.gifView.animationDuration = [self.stateDurations[@(state)] doubleValue];
            [self.gifView startAnimating];
        }
    } else if (state == MJRefreshStateIdle) {
        [self.gifView stopAnimating];
    }
}
@end
