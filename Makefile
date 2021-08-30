BUNDLE = lv2pftci-pansinoscMUS.lv2
INSTALL_DIR = /usr/local/lib/lv2

$(BUNDLE): manifest.ttl pansinoscMUS.ttl pansinoscMUS.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl pansinoscMUS.ttl pansinoscMUS.so $(BUNDLE)

pansinoscMUS.so: pansinoscMUS.cpp
	g++ -shared -fPIC -DPIC pansinoscMUS.cpp `pkg-config --cflags --libs lv2-plugin` -o pansinoscMUS.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) pansinoscMUS.so
