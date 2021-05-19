#!/bin/bash
if [ "$1" == "" ]; then
  echo "please input image_name and  container_name  to start
  usage: $0 [image_name] [container_name]
"
  exit 0
fi

image_name=$1
container_name=$2

nvidia_smi_path=`which nvidia-smi`

GPU_OPTIONS="--gpus all"
if [ -z "${nvidia_smi_path}" ]; then
  GPU_OPTIONS=""
fi

# docker run ${GPU_OPTIONS} -d --network host --privileged --name ${CONTAINER_NAME} \
docker run ${GPU_OPTIONS} -d --privileged --name ${container_name} \
  --env="DISPLAY" \
  --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
  -v /dev:/dev \
  -v /home/nvidia/shared_dir:/home/shared_dir \
  -v /home/nvidia/.Xauthority:/root/.Xauthority \
  -it ${image_name} /bin/bash