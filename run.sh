#!/bin/sh

sudo systemctl restart pcscd.socket
python3 code_pds_mem_partagee_enzo.py
sudo ./dev/bin/IHM_Station
