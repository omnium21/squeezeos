#!/bin/bash

set -e

echo "Building squeezeos image builder..."
docker build -t squeezeos_builder .
if docker ps -a | grep -q squeezeos_builder
then
	echo "Deleting previous version of squeezeos builder container..."
	docker stop squeezeos_builder
	docker rm -f squeezeos_builder
fi

echo "Starting squeezeos image builder..."

docker run -it --name squeezeos_builder -v ${PWD}/../poky:/home/squeezeos/poky squeezeos_builder /bin/bash
