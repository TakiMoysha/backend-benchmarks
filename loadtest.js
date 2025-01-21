import http from "k6/http";
import { check } from "k6";

export const options = {
  stages: [
    {
      duration: "10s",
      target: 1000,
    },
    {
      duration: "10s",
      target: 10000,
    },
    {
      duration: "10s",
      target: 500,
    },
  ]
  // scenarios: {
  //   loadtesting: {
  //     executor: "shared-iterations",
  //     vus: 100,
  //     iterations: 1000
  //   }
  // }
}

export default function () {
  const res = http.get(`http://127.0.0.1:8000/api/orders`);
  check(res, { "status was 200": (r) => r.status == 200 });
}
