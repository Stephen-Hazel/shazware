#!/usr/bin/env php
<?php # go - flathub publish

system ("echo ---cp _build");
system ("rm -fr _build");
system ("cp -pr ../sh/_build .");

system ("echo ---uninstall");
system ("flatpak uninstall -y app.pianocheetah.shazware");

system ("echo ---del local repo");
system ("flatpak --force remote-delete sh_repo");

system ("echo ---pseudo rebuild _build into _repo, _xbuild");
system ("rm -fr .flatpak-builder");
system ("rm -fr _repo");   system ("rm -fr _xbuild");   
system ("mkdir  _repo");   system ("mkdir  _xbuild");
system ("flatpak-builder --repo=_repo _xbuild app.pianocheetah.shazware.json");
system ("rm -fr .flatpak-builder _xbuild");

system ("echo ---add remote");
system ("flatpak remote-add --no-gpg-verify sh_repo _repo");

system ("echo ---install");
system ("flatpak install --noninteractive sh_repo app.pianocheetah.shazware");

#system ("rm -fr ~/.var/app/app.pianocheetah.sh*");
