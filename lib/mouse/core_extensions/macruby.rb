framework 'AppKit'

# A workaround that guarantees that `CGPoint` is defined
unless defined? MOUNTAIN_LION_APPKIT_VERSION
  MOUNTAIN_LION_APPKIT_VERSION = 1187
end

if NSAppKitVersionNumber >= MOUNTAIN_LION_APPKIT_VERSION
  framework '/System/Library/Frameworks/CoreGraphics.framework'
end
