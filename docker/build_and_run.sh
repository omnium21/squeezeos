#!/bin/bash

set -e

echo "Building squeezeos image builder..."
docker build -t squeezeos_builder .
if docker ps -a | grep -q squeezeos_builder
then
	echo "Stopping previous version of squeezeos builder container..."
	docker stop squeezeos_builder
fi

echo "Starting squeezeos image builder..."
docker run -it --rm  -v ${PWD}/../:/home/squeezeos/ squeezeos_builder
