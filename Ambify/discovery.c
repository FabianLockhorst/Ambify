#include <windows.h>
#include <stdio.h>
#include <Wingdi.h>


int discovery()
{
    
}











/* 
 * ######################################
 * #            -Ruby example-          #
 * ###################################### 
 */

/*class HueController < Sinatra::Base
  post "/discover" do
    socket  = UDPSocket.new(Socket::AF_INET)
    socket.send("M-SEARCH * HTTP/1.1\nHOST: 239.255.255.250:1900\nMAN: ssdp:discover\nMX: 10\nST: ssdp:all", 0, "239.255.255.250", 1900)

    begin
      Timeout.timeout(5) do
        while true do
          res, meta = socket.recvfrom(256)
          if res =~ /description\.xml/
            # Confirm that it's actually a Philips Hue hub
            require "net/http"
            http = Net::HTTP.new(meta[2], 80)
            res = http.request_get("/description.xml")
            # Quick way of confirming it, better ways of doing it naturally
            if res.body =~ /Philips hue/i
              break [200, meta[2]]
            end
          end
        end
      end

    rescue Timeout::Error
      400
    end
  end
end*/
