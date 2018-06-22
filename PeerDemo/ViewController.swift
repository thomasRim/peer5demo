//
//  ViewController.swift
//  PeerDemo
//
//  Created by Volodymyr Yevdokymov on 6/11/18.
//  Copyright © 2018 PrometheanTV. All rights reserved.
//

import UIKit
import Peer5Kit
import AVKit

class ViewController: UIViewController {

    let peer = Peer5Sdk.init(token: "yqxmmt7dmk7fr915rqcw") 
    let avPlayer = AVPlayer()
    var avPlayerLayer: AVPlayerLayer?
    
    @IBOutlet weak fileprivate var playerView: UIView?
    @IBOutlet weak fileprivate var sourceTF: UITextField?
    @IBOutlet weak fileprivate var playBtn: UIButton?
    @IBOutlet weak fileprivate var stopBtn: UIButton?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.stopPlaying()
        
        self.sourceTF?.text = "https://qa.embed.promethean.tv?autoplay=false&channel=5afe7b941e8e7d06ddca9396"
    }

    //MARK: - Actions
    
    @IBAction fileprivate func onPlay() {
        self.playStream()
    }
    
    @IBAction fileprivate func onStop() {
        self.stopPlaying()
    }
    //MARK: - Privates

    fileprivate func playStream() {
        if let url = URL(string: self.sourceTF?.text ?? "") {
            let streamURL = peer.streamURL(forURL: url)
            
            print("Peer stream url \(streamURL)")
            
            self.preparePlayer()
            
            let playerItem = AVPlayerItem(url: streamURL)
            self.avPlayer.replaceCurrentItem(with: playerItem)
            self.avPlayer.play()
            
            self.playBtn?.isEnabled = false
            self.stopBtn?.isEnabled = true
        }
    }
    
    fileprivate func stopPlaying() {
        self.avPlayer.pause()
        self.avPlayerLayer?.removeFromSuperlayer()
        
        self.playBtn?.isEnabled = true
        self.stopBtn?.isEnabled = false
    }
    
    fileprivate func preparePlayer() {
        self.avPlayerLayer = AVPlayerLayer(player: self.avPlayer)
        self.avPlayerLayer?.frame = self.playerView?.bounds ?? .zero
        if let layer = self.avPlayerLayer {
            self.playerView?.layer.addSublayer(layer)
        }
    }
}

extension ViewController: UITextFieldDelegate {
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        return true
    }
}

