PSs=""

python print_sync_info.py el &
PSs="$PSs $!"

python print_sync_info.py mu &
PSs="$PSs $!"

wait $PSs

