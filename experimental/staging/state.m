#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <TesseractOCR/TesseractOCR.h>

@interface TextRecognition : NSObject

@property (nonatomic, strong) Tesseract* tesseract;
@property (nonatomic, strong) NSImage* lastFrame;
@property (nonatomic, strong) NSMutableArray<NSValue*>* rois;
@property (nonatomic, assign) NSRect currentROI;
@property (nonatomic, assign) BOOL drawing;
@property (nonatomic, assign) BOOL running;

- (void)start;

- (void)readText:(NSImage*)frame;

- (void)printRoiData:(NSDictionary*)roiData;

- (NSDictionary*)extractLabelAndValue:(NSString*)text;

- (void)displayWindow;

- (void)onMouseEvents:(NSEvent*)event;

- (void)videoProcessingThread;

- (void)removeLastRoi;

- (void)undoRoiDeletion;

- (void)handleUserInput;

@end

@implementation TextRecognition

- (instancetype)init {
    self = [super init];
    if (self) {
        self.tesseract = [[Tesseract alloc] initWithLanguage:@"eng"];
        self.lastFrame = nil;
        self.rois = [NSMutableArray array];
        self.currentROI = NSZeroRect;
        self.drawing = NO;
        self.running = YES;
    }
    return self;
}

- (void)start {
    [self videoProcessingThread];
    [self handleUserInput];
    [self displayWindow];
}

- (void)readText:(NSImage*)frame {
    if (frame == nil) {
        return;
    }

    NSMutableDictionary* roiData = [NSMutableDictionary dictionary];

    for (NSValue* roiValue in self.rois) {
        NSRect roi = [roiValue rectValue];
        NSImage* croppedFrame = [frame imageCroppedToRect:roi];
        [self.tesseract setImage:croppedFrame];
        [self.tesseract recognize];
        NSString* text = [self.tesseract recognizedText];

        NSMutableDictionary* roiInfo = [NSMutableDictionary dictionary];
        NSMutableArray* listValue = [NSMutableArray array];

        NSRegularExpression* regex = [NSRegularExpression regularExpressionWithPattern:@"([a-zA-Z]+)\\s*([0-9]+\\.?[0-9]*)" options:0 error:nil];
        NSArray<NSTextCheckingResult*>* matches = [regex matchesInString:text options:0 range:NSMakeRange(0, text.length)];

        for (NSTextCheckingResult* match in matches) {
            NSString* label = [text substringWithRange:[match rangeAtIndex:1]];
            NSString* value = [text substringWithRange:[match rangeAtIndex:2]];
            [listValue addObject:@(value.floatValue)];

            if (label.length > 0) {
                if (roiInfo[label] == nil) {
                    roiInfo[label] = [NSMutableArray array];
                }
                [roiInfo[label] addObject:@(value.floatValue)];
            }
        }

        NSString* roiId = [NSString stringWithFormat:@"ROI_ID %lu", (unsigned long)[self.rois indexOfObject:roiValue]];
        roiData[roiId] = roiInfo;
    }

    // Printing JSON and printing ROI data goes here
    NSLog(@"%@", roiData);
    [self printRoiData:roiData];
}

- (void)printRoiData:(NSDictionary*)roiData {
    // Your code to print ROI data goes here
}

- (NSDictionary*)extractLabelAndValue:(NSString*)text {
    NSRegularExpression* regex = [NSRegularExpression regularExpressionWithPattern:@"([a-zA-Z]+)\\s*([0-9]+\\.?[0-9]*)" options:0 error:nil];
    NSTextCheckingResult* match = [regex firstMatchInString:text options:0 range:NSMakeRange(0, text.length)];

    if (match) {
        NSString* label = [text substringWithRange:[match rangeAtIndex:1]];
        NSString* value = [text substringWithRange:[match rangeAtIndex:2]];
        return @{@"label": label, @"value": value};
    } else {
        return @{@"label": @"", @"value": @""};
    }
}

- (void)displayWindow {
    NSApplication* app = [NSApplication sharedApplication];
    NSWindow* window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 800, 600) styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable) backing:NSBackingStoreBuffered defer:NO];
    [window setTitle:@"Text Recognition"];

    [app run];
}

- (void)onMouseEvents:(NSEvent*)event {
    NSPoint point = [event locationInWindow];
    NSRect frameRect = [self.lastFrame alignmentRect];
    NSPoint mouseLocation = [self.lastFrame convertPoint:point fromView:nil];

    if (event.type == NSEventTypeLeftMouseDown) {
        self.drawing = YES;
        self.currentROI = NSMakeRect(mouseLocation.x, mouseLocation.y, 0, 0);
    } else if (event.type == NSEventTypeLeftMouseUp) {
        self.drawing = NO;
        [self.rois addObject:[NSValue valueWithRect:self.currentROI]];
        self.currentROI = NSZeroRect;
    } else if (self.drawing && event.type == NSEventTypeLeftMouseDragged) {
        self.currentROI.size = NSMakeSize(mouseLocation.x - self.currentROI.origin.x, mouseLocation.y - self.currentROI.origin.y);
    }
}

- (void)videoProcessingThread {
    while (self.running) {
        // Capture video frame and process it
        NSImage* frame = [self captureVideoFrame];
        [self readText:frame];
    }
}

- (NSImage*)captureVideoFrame {
    // Your code to capture video frame goes here
    return nil;
}

- (void)removeLastRoi {
    if (self.rois.count > 0) {
        [self.rois removeLastObject];
    }
}

- (void)undoRoiDeletion {
    // Your code to undo ROI deletion goes here
}

- (void)handleUserInput {
    while (self.running) {
        NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskKeyDown | NSEventMaskFlagsChanged untilDate:[NSDate distantFuture] inMode:NSDefaultRunLoopMode dequeue:YES];

        if (event) {
            NSString* characters = [event characters];
            unichar keyChar = [characters characterAtIndex:0];

            if (keyChar == 'q' || [event keyCode] == 53) {  // 'q' or ESC key
                self.running = NO;
            } else if (keyChar == 'd') {
                [self removeLastRoi];
            } else if (keyChar == 'u') {
                [self undoRoiDeletion];
            }
        }
    }
}

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        TextRecognition *textRecognition = [[TextRecognition alloc] init];
        [textRecognition start];
    }
    return 0;
}
