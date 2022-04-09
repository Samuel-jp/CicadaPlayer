#
#  Be sure to run `pod spec lint CicadaPlayer.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see https://guides.cocoapods.org/syntax/podspec.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |spec|
  # 基础信息
  spec.name = "CicadaPlayer"
  spec.version = "0.4.1"
  spec.source = { :git => "https://github.com/alibaba/CicadaPlayer.git", :tag => "#{spec.version}" }
  # 描述信息
  spec.summary = "CicadaPlayer is the player core of AliPlayer."
  spec.description = <<-DESC 
  CicadaPlayer is the player core of AliPlayer, which support multiple platform Android, iOS, macOS, Windows, Linux, and WebAssembly for now. The goal is providing a player core which support multi platform, hardware accelerator, customizable and extensible features. Which support WideVine drm and LL-HLS dash.
  DESC
  spec.homepage = "https://github.com/alibaba/CicadaPlayer"
  spec.license = { :type => "MIT", :text => <<-LICENSE
  Copyright (c) 2019-present Alibaba Inc.
  LICENSE
  }
  spec.author = {
      # 集成者
      "mamba" => "mambaxie@gmail.com",
      # 提供者
      "Tony Liu" => "shengqiang@luminesence.jp"
  }
  # 源码，头文件，库文件
  spec.vendored_frameworks = 'platform/Apple/products/CicadaPlayerSDK.framework', 'platform/Apple/products/alivcffmpeg.framework'
  # 编译选项
  spec.ios.deployment_target = '11.0'
  spec.pod_target_xcconfig = { 'VALID_ARCHS' => 'armv7 arm64' }
end

