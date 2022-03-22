## Geostats (WIP)
Backend service for GeoStats application. Service parses locally stored *.csv files, creates SQLite DB, tables and seeds data. Service also creates following REST API endpoints and run server at port `8080`:
- **GET** http://localhost:8080/asia
- **GET** http://localhost:8080/europe
- **GET** http://localhost:8080/africa
- **GET** http://localhost:8080/north_america
- **GET** http://localhost:8080/south_america
- **GET** http://localhost:8080/oceania
- **GET** http://localhost:8080/antarctica
- **GET** http://localhost:8080/indian_ocean
- **GET** http://localhost:8080/atlantic_ocean
- **GET** http://localhost:8080/arctic_ocean
- **GET** http://localhost:8080/pacific_ocean
- **GET** http://localhost:8080/southern_ocean
- **GET** http://localhost:8080/physical_geography
- **GET** http://localhost:8080/political_urban_geography
- **GET** http://localhost:8080/economic_geography
- **GET** http://localhost:8080/indicators

## Build

### Dependencies

This is a **cmake** project. Following libraries will be fetched by **cmake** automatically by `FetchContent_Declare`:
* **cpp-httplib**: https://github.com/yhirose/cpp-httplib
* **json**: https://github.com/nlohmann/json
* **sqlite3-cmake**: https://github.com/alex85k/sqlite3-cmake

### Build for Debug profile
```
$ mkdir cmake-build-debug
$ cd cmake-build-debug
$ cmake ../
$ cmake --build . --target geostats_cvs_parser --config Debug
```

### Build for Release profile
```
$ mkdir cmake-build-release
$ cd cmake-build-release
$ cmake ../
$ cmake --build . --target geostats_cvs_parser --config Release
```

## Run
Copy *.csv files to `/csv` folder and run:

Debug profile:
`./cmake-build-debug/geostats_cvs_parser`

Release profile:
`./cmake-build-release/geostats_cvs_parser`

## Deploy on AWS ECS Fargate Cluster using ECR storage

#### 1. Build a docker container
Run following command from project root folder. Use `--platform linux/amd64` on Apple M1.
```
docker build . -t cmake-geostats-app --network=host --platform linux/amd64
```

#### 2. Create AWS ECR repository (if doesn't exist)
```
aws ecr create-repository --repository-name geostats-server-repository --region eu-west-2
```

#### 3. Tag docker image with aws ecr location
```
docker tag cmake-geostats-app {your-aws-id}.dkr.ecr.eu-west-2.amazonaws.com/geostats-server-repository
```

#### 4. Login to AWS ECR 
```
aws ecr get-login-password | docker login --username AWS --password-stdin {your-aws-id}.dkr.ecr.eu-west-2.amazonaws.com
```

#### 5. Push container to AWS ECR
```
docker push {your-aws-id}.dkr.ecr.eu-west-2.amazonaws.com/geostats-server-repository
```

Following steps are better explained in following article by AWS:
https://aws.amazon.com/getting-started/hands-on/break-monolith-app-microservices-ecs-docker-ec2/

#### 6. Create AWS ECS Cluster using YAML configuration file

https://aws.amazon.com/getting-started/hands-on/break-monolith-app-microservices-ecs-docker-ec2/module-two/

Run AWS Cloud Formation template file [here](https://github.com/awslabs/amazon-ecs-nodejs-microservices/blob/master/2-containerized/infrastructure/ecs.yml).
